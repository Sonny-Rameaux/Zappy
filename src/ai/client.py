from network import Connection
from args_parsing import parse_args
from args_parsing import errorParsing
from player import Player
import sys
import time

def ai_logic(player: Player):
    player.messages = []
    player.filtered_messages = []
    player.broadcast("Hello")
    if player.lvl == 4 and player.mainI == True and player.ready5 == False:
        player.broadcast("Final")
    player.inventoryCmd()
    player.look()
    player.getMessages()
    player.getBroadcastMessages()
    player.setDecision()
    player.takeDecision()


def connectToServer(arguments: dict) -> Player:
    connecting = Connection(arguments)

    response = connecting.recv()
    print(response)
    connecting.send(arguments["name"] + "\r\n")
    response = connecting.recv()
    print(response)
    if response == "ko":
        print("Wrong team name or not enough slots avaiable")
        sys.exit(84)
    dimensions = response.replace("\r\n", "").split(" ")
    width = int(dimensions[0])
    height = int(dimensions[1])
    connecting.recv()
    return Player(width, height, connecting, arguments)

def main():
    try:
        arguments = parse_args()
    except errorParsing as e:
        print(e)
        sys.exit(0)

    mainPlayer = connectToServer(arguments)
    while True:
        ai_logic(mainPlayer)


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("\nInterrupted by user!")
