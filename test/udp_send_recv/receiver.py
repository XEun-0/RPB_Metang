import socket

LISTEN_IP = "0.0.0.0"
LISTEN_PORT = 5005
BUFFER_SIZE = 4096

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((LISTEN_IP, LISTEN_PORT))

with open("received.pdf", "wb") as f:
    while True:
        data, addr = sock.recvfrom(BUFFER_SIZE)
        if data == b"EOF":
            break
        f.write(data)

print("File received.")
