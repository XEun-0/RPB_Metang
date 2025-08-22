import socket

SERVER_IP = "192.168.1.50"  # Replace with Raspberry Pi IP
SERVER_PORT = 5005
BUFFER_SIZE = 4096

filename = "test.pdf"  # File to send

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

with open(filename, "rb") as f:
    chunk = f.read(BUFFER_SIZE)
    while chunk:
        sock.sendto(chunk, (SERVER_IP, SERVER_PORT))
        chunk = f.read(BUFFER_SIZE)

# Send end marker
sock.sendto(b"EOF", (SERVER_IP, SERVER_PORT))
print("File sent.")
