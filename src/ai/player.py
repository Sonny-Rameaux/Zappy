from network import Connection
from abc import ABC, abstractmethod
import sys
import subprocess
import signal
import time

class State(ABC):
    @abstractmethod
    def take_decision(self, player):
        pass

    @abstractmethod
    def getName(self):
        pass

class FoodState(State):
    def take_decision(self, player):
        player.moveTo("food")

    def getName(self):
        return "Food"

class StoneState(State):
    def take_decision(self, player):
        player.moveTo(player.whichStone())

    def getName(self):
        return "Stone"

class IncantationState(State):
    def take_decision(self, player):
        if player.lvl == 1:
            player.incantation()
        else:
            player.parseLook(player.look())
            while player.lookedTiles[0]["player"] < player.currentObjective["player"]:
                player.parseInventory(player.inventoryCmd())
                if player.inventory["food"] < 10:
                    print("I need more food, canceling...")
                    player.broadcast("OK")
                    player.priority = FoodState()
                    return
                print("debug", player.send_command("debug"))
                print(player.lookedTiles[0]["player"], "out of", player.currentObjective["player"])
                player.parseLook(player.look())
                player.broadcast("Ready for level " + str(player.lvl + 1))
            print(player.lookedTiles[0]["player"], "out of", player.currentObjective["player"])
            incanting = player.incantation()
            print("Incanting...", incanting)
            time.sleep(0.5)
            if incanting != "ko":
                print("Broadcast",player.broadcast("OK"))
                print("Incantation successful!")
                if player.lvl == 4:
                    player.mainI = True
            player.directions_to_tile(3)

    def getName(self):
        return "Incantation"

class GoToIncantationState(State):
    def take_decision(self, player):
        while player.directionToGo != 0:
            whereTo = player.decodeMessage(player.socket.recv())
            if "OK" in whereTo:
                player.priority = FoodState()
                return
            if "Ready" in whereTo:
                player.goToInteractionDirection()
        whereTo = player.decodeMessage(player.socket.recv())
        while not "OK" in whereTo:
            print("Broadcast result:", whereTo)
            if "Hello" in whereTo:
                print("couldn't level up :(")
                player.priority = FoodState()
                return
            whereTo = player.decodeMessage(player.socket.recv())
        print("whereTo end", whereTo)
        player.lvl += 1
        print("Level up", player.lvl)
        player.currentObjective = player.objectives.inventoryObjective[player.lvl - 1]
        player.directions_to_tile(9)
        player.priority = FoodState()

    def getName(self):
        return "GoToIncantation"

class TimeoutException(Exception):
    pass

def timeout_handler(signum, frame):
    raise TimeoutException()

signal.signal(signal.SIGALRM, timeout_handler)

class Objectives:
    def __init__(self) -> None:
        self.inventoryObjective = [
            {"player" : 1, "linemate" : 1, "deraumere" : 0, "sibur" : 0, "mendiane" : 0, "phiras" : 0, "thystame" : 0},
            {"player" : 2, "linemate" : 1, "deraumere" : 1, "sibur" : 1, "mendiane" : 0, "phiras" : 0, "thystame" : 0},
            {"player" : 2, "linemate" : 2, "deraumere" : 0, "sibur" : 1, "mendiane" : 0, "phiras" : 2, "thystame" : 0},
            {"player" : 4, "linemate" : 1, "deraumere" : 1, "sibur" : 2, "mendiane" : 0, "phiras" : 1, "thystame" : 0},
            {"player" : 4, "linemate" : 1, "deraumere" : 2, "sibur" : 1, "mendiane" : 3, "phiras" : 0, "thystame" : 0},
            {"player" : 6, "linemate" : 1, "deraumere" : 2, "sibur" : 3, "mendiane" : 0, "phiras" : 1, "thystame" : 0},
            {"player" : 6, "linemate" : 2, "deraumere" : 2, "sibur" : 2, "mendiane" : 2, "phiras" : 2, "thystame" : 1}
        ]

class Player:
    def __init__(self, width: int, height: int, socket: Connection, arguments: dict) -> None:
        self.arguments = arguments

        self.isAlive = True
        self.mapWidth = width
        self.mapHeigth = height
        self.socket = socket
        self.objectives = Objectives()
        self.lvl = 1
        self.currentObjective = self.objectives.inventoryObjective[self.lvl - 1]
        self.priority = FoodState()

        self.inventory = {}
        self.lookedTiles = []
        self.messages = []
        self.filtered_messages = []

        self.directionToGo = None

        self.direction = 0
        self.decodedMessage = ""

        self.ready5 = False
        self.mainI = False

    def decodeMessage(self, message):
        self.decodedMessage = ""
        for letter in message:
            if 'A' <= letter <= 'Z':
                new = ord(letter) - self.direction
                if new < ord('A'):
                    new += 26
                self.decodedMessage += chr(new)
            elif 'a' <= letter <= 'z':
                new = ord(letter) - self.direction
                if new < ord('a'):
                    new += 26
                self.decodedMessage += chr(new)
            elif '0' <= letter <= '9':
                new = ord(letter) - self.direction
                if new < ord('0'):
                    new += 10
                self.decodedMessage += chr(new)
            else:
                self.decodedMessage += letter

    def receive_commands(self):
        while True:
            try:
                response = self.socket.recv()
                if response is None:
                    break
                self.command_queue.put(response)
            except Exception as e:
                print(f"Error receiving commands: {e}")
                break

    def send_command(self, command: str):
        self.socket.send(command)
        response = self.socket.recv()
        if response == "dead":
            print("oh no you died")
            sys.exit(0)
        while "message" in response:
            self.filtered_messages.append(response.replace("\r", " ")[:-1])
            response = self.socket.recv()
        self.messages.append(response)
        return response

    def wait_command(self):
        response = self.socket.recv()
        return response

    def look(self):
        return self.send_command("Look")

    def take(self, item: str):
        return self.send_command(f"Take {item}")

    def inventoryCmd(self):
        return self.send_command("Inventory")

    def move_forward(self):
        return self.send_command("Forward")

    def turn_right(self):
        return self.send_command("Right")

    def turn_left(self):
        return self.send_command("Left")

    def incantation(self):
        response = self.send_command("Incantation")
        if response != "ko":
            self.lvl += 1
            self.currentObjective = self.objectives.inventoryObjective[self.lvl - 1]
            print("Incantation level up", self.lvl)
        return response

    def broadcast(self, message: str):
        return self.send_command(f"Broadcast {message}")

    def fork(self):
        response = self.send_command("Fork")
        print("forked:", response)
        # if response == "ok": ## COMMENTER ÇA POUR PLUS AVOIR LES FORKS
        #     self.createEgg() ## COMMENTER ÇA POUR PLUS AVOIR LES FORKS
        return response

    def parseLook(self, look: str):
        self.lookedTiles = []
        segments = look[1:-1].split(',')
        nb = look.count(",")
        for i in range(nb + 1):
            dico = {
                "case": i,
                "player": 0,
                "food": 0,
                "linemate": 0,
                "deraumere": 0,
                "sibur": 0,
                "mendiane": 0,
                "phiras": 0,
                "thystame": 0,
                "egg": 0
            }
            subsegments = segments[i].split()
            for item in subsegments:
                resource, quantity = item.split('_')
                dico[resource] = int(quantity)
            self.lookedTiles.append(dico)

    def parseInventory(self, inventory: str):
        self.inventory = {}
        items = ["linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame", "food"]
        list_inventory = inventory[1:-1].split(', ')
        self.inventory = {item.split()[0]: int(item.split()[1]) for item in list_inventory}
        for i in range(len(items)):
            if self.inventory.get(items[i]) == None:
                self.inventory.setdefault(items[i], 0)

    def whichStone(self):
        for key, value in self.currentObjective.items():
            if key != "player" and key != "food":
                if value != 0:
                    if self.inventory[key] < self.currentObjective[key]:
                        print("searching for", key)
                        return key
        return "sibur"

    def isReadyToLevelUp(self):
        for key, value in self.currentObjective.items():
            if key != "player":
                if value != 0:
                    if self.inventory[key] < self.currentObjective[key]:
                        return False
        return True

    def setDecision(self):
        self.getBroadcastMessages()
        if self.priority.getName() == "GoToIncantation":
            print("I will go to the incantation")
            return
        if self.inventory["food"] <= 5:
            self.priority = FoodState()
        elif self.inventory["food"] >= 11 and self.isReadyToLevelUp() == False:
            self.priority = StoneState()
        elif self.inventory["food"] >= 20 and self.isReadyToLevelUp() == True and self.priority != GoToIncantationState() and not self.goToCheck() and self.lvl == 1:
            self.fork()
            self.priority = IncantationState()
        elif self.inventory["food"] >= 50 and self.isReadyToLevelUp() == True and self.priority != GoToIncantationState() and not self.goToCheck() and self.lvl > 1 and self.lvl != 4:
            self.fork()
            self.priority = IncantationState()
        elif self.inventory["food"] >= 50 and self.isReadyToLevelUp() == True and self.priority != GoToIncantationState() and not self.goToCheck() and self.lvl >= 4 and self.ready5 == True:
            self.priority = IncantationState()
        else:
            self.priority = FoodState()
        print("State changed to:", self.priority.getName())

    def findWhereToGo(self, toTake: str):
        toTakeCmp = 0
        candidate = 0
        for i in range(len(self.lookedTiles)):
            value = self.lookedTiles[i][toTake]
            if value > toTakeCmp and self.lookedTiles[i]["player"] == 0:
                toTakeCmp = self.lookedTiles[i][toTake]
                candidate = self.lookedTiles[i]["case"]
        return candidate

    def directions_to_tile(self, num: int):
        if num == 0:
            return
        if num == 1:
            self.move_forward()
            self.turn_left()
            self.move_forward()
            return
        layer = 1
        tile_num = 0
        while True:
            start_tile = tile_num + 1
            num_tiles_in_layer = 2 * layer - 1
            end_tile = start_tile + num_tiles_in_layer - 1
            if start_tile <= num <= end_tile:
                position_in_layer = num - start_tile
                break
            tile_num = end_tile
            layer += 1
        for _ in range(layer - 1):
            self.move_forward()
        middle_index = ((num_tiles_in_layer - 1) // 2) - 1
        if position_in_layer < middle_index:
            self.turn_left()
            for _ in range(middle_index - position_in_layer):
                self.move_forward()
        elif position_in_layer > middle_index:
            self.turn_right()
            for _ in range(position_in_layer - middle_index):
                self.move_forward()

    def limiter(self, concerned: str) -> int:
        if "food" in concerned:
            return 30
        else:
            return 10

    def moveTo(self, toTake: str):
        index = self.findWhereToGo(toTake)
        if index != 0:
            self.directions_to_tile(index)
        limit = min(self.lookedTiles[index][toTake], self.limiter(toTake))
        print("Taking", toTake,":", limit, "times")
        for _ in range(limit):
            try:
                signal.alarm(5)
                takeMsg = self.take(toTake)
                signal.alarm(0)
                if takeMsg == "dead":
                    print("You died")
                    sys.exit(84)
                if "ok" not in takeMsg:
                    print("weird ?", takeMsg)
                if "message" in takeMsg:
                    takeMsg = self.take(toTake)
                if takeMsg == "ko":
                    print("broken pipe")
                    return
            except TimeoutException:
                print("Operation timed out")
                break

    def filter_messages(self):
        self.filtered_messages = [msg for msg in self.messages if "message" in msg]
        for msg in self.messages:
            if "message" in msg:
                self.messages.remove(msg)

    def getMessages(self):
        for elt in self.messages:
            if "_" in elt:
                self.parseLook(elt)
            elif "[" and "]" in elt:
                print("Inventory", elt)
                self.parseInventory(elt)
            else:
                pass

    def decodeMessage(self, message: str):
        try:
            message = message[7:]
            decodedMessage = ""
            self.directionToGo = int(message.split(",")[0])
            for letter in message:
                if 'A' <= letter <= 'Z':
                    new = ord(letter) - self.directionToGo
                    if new < ord('A'):
                        new += 26
                    decodedMessage += chr(new)
                elif 'a' <= letter <= 'z':
                    new = ord(letter) - self.directionToGo
                    if new < ord('a'):
                        new += 26
                    decodedMessage += chr(new)
                else:
                    decodedMessage += letter
            return "message" + decodedMessage
        except ValueError:
            return ""
        except IndexError:
            return ""

    def goToCheck(self):
        for elt in self.filtered_messages:
            elt2 = self.decodeMessage(elt)
            if "Ready for level" in elt2:
                return True
        return False

    def getBroadcastMessages(self):
        for elt in self.filtered_messages:
            elt2 = self.decodeMessage(elt)
            print("elt2", elt2)
            if "Final" in elt2 and self.lvl == 4:
                self.ready5 = True
            if "Ready for level" in elt2:
                proposalLvl = int(elt2.split("Ready for level ")[1])
                if proposalLvl == self.lvl + 1:
                    self.priority = GoToIncantationState()
                    return
                else:
                    print("aint for me bud I can only upgrade to", self.lvl + 1, "not", proposalLvl)
            if "OK" in elt2:
                print("Incantation already done")
                self.priority = FoodState()
            else:
                print("They're spitting nonsense")

    def goToInteractionDirection(self):
        print("debug", self.send_command("debug"))
        if self.directionToGo == 1:
            self.move_forward()
        if self.directionToGo == 2:
            self.move_forward()
            self.turn_left()
            self.move_forward()
        if self.directionToGo == 3:
            self.turn_left()
            self.move_forward()
        if self.directionToGo == 4:
            self.turn_left()
            self.move_forward()
            self.turn_left()
            self.move_forward()
        if self.directionToGo == 5:
            self.turn_left()
            self.turn_left()
            self.move_forward()
        if self.directionToGo == 6:
            self.turn_right()
            self.move_forward()
        if self.directionToGo == 7:
            self.turn_right()
            self.move_forward()
        if self.directionToGo == 8:
            self.move_forward()
            self.turn_right()
            self.move_forward()

    def createEgg(self):
        print("Created an egg")
        with open('output.log', 'w') as f_out, open('error.log', 'w') as f_err:
            process = subprocess.Popen(
                ['python3', 'src/ai/client.py', '-p', str(self.arguments["port"]), '-n', self.arguments["name"], '-h', self.arguments["host"]],
                stdout=f_out,
                stderr=f_err,
                text=True
            )

    def takeDecision(self):
        self.priority.take_decision(self)
