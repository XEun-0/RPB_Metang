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