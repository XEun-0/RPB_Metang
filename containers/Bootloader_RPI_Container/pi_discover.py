import socket

UDP_IP = "255.255.255.255"
UDP_PORT = 5005

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

sock.sendto(b"whereareyou", (UDP_IP, UDP_PORT))
sock.settimeout(3)

try:
    data, addr = sock.recvfrom(1024)
    print(f"Pi responded from {addr[0]} with IP: {data.decode()}")
except socket.timeout:
    print("No Pi found.")
