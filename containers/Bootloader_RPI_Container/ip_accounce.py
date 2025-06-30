#!/usr/bin/env python3
import socket

UDP_PORT = 5005

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(("", UDP_PORT))

print("[*] Waiting for UDP discovery ping...")
while True:
    data, addr = sock.recvfrom(1024)
    if data.decode().strip() == "whereareyou":
        ip = socket.gethostbyname(socket.gethostname())
        print(f"[x] Received discovery from {addr}, sending IP: {ip}")
        sock.sendto(ip.encode(), addr)
