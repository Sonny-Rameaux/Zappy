import socket
import sys
import select

class Connection:
    def __init__(self, args: dict) -> None:
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            self.socket.connect((args["host"], args["port"]))
        except ConnectionRefusedError:
            print("Couldn't connect to server on " + args["host"] + ":" + str(args["port"]))
            sys.exit(84)
        self.socket.settimeout(0)
        self.buffer = ""

    def send(self, message: str) -> None:
        self.socket.send((message + "\r\n").encode())

    def recv(self):
        while "\r\n" not in self.buffer:
            try:
                read_ready, _, _ = select.select([self.socket], [], [], 0)
                if read_ready:
                    self.buffer += self.socket.recv(1024).decode()
            except select.error:
                print("Select error")
                sys.exit(84)
        
        messages = self.buffer.split("\r\n")
        receivedMessage = messages[0]
        self.buffer = ""
        return receivedMessage

    def stop(self):
        self.socket.close()