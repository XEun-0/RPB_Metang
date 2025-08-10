🚀 Setup Instructions on Raspberry Pi
Install Docker & Docker Compose

bash
Copy
Edit
sudo apt update
sudo apt install docker.io docker-compose
sudo usermod -aG docker $USER
Build and Start

bash
Copy
Edit
cd printer-setup
docker-compose up -d --build
Access Web UI (from another PC on same network)

cpp
Copy
Edit
http://<raspberry_pi_ip>:631

# 6/30/2025
lsusb

dmesg | grep -i usb

ls /dev/usb*
ls /dev/bus/usb/*

sudo apt install hplip hplip-gui printer-driver-hpijs

# hp specific
fjura@fjura:~$ hp-setup
hp-plugin -i
sudo hp-setup -i