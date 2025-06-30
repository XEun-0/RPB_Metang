#!/bin/bash
set -e

IMG=output/pi_bootloader.img
BOOT_MB=256
IMAGE_SIZE_MB=1024
WIFI_SSID=${WIFI_SSID:-"YourSSID"}
WIFI_PASS=${WIFI_PASS:-"YourPassword"}
TARGET_HOSTNAME="rpi-bootloader"
RPI_OS_IMG="raspios_lite_armhf_latest.zip"
RPI_OS_IMG_URL="https://downloads.raspberrypi.org/raspios_lite_armhf_latest"

mkdir -p output tmp rootfs bootfs

echo "[*] Downloading Raspberry Pi OS Lite base image..."
wget -qO "output/${RPI_OS_IMG}" "$RPI_OS_IMG_URL"

echo "[*] Extracting base image..."
unzip -o "output/${RPI_OS_IMG}" -d output/
BASE_IMG=$(find output -name '*.img' | head -n1)

echo "[*] Mounting image partitions..."
LOOPDEV=$(losetup --show -fP "$BASE_IMG")
mkdir -p /mnt/boot /mnt/root
mount ${LOOPDEV}p1 /mnt/boot
mount ${LOOPDEV}p2 /mnt/root

echo "[*] Enabling SSH..."
touch /mnt/boot/ssh

echo "[*] Setting up Wi-Fi config..."
cat > /mnt/boot/wpa_supplicant.conf <<EOF
ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
update_config=1
country=US

network={
    ssid=\"${WIFI_SSID}\"
    psk=\"${WIFI_PASS}\"
}
EOF

echo "[*] Setting hostname..."
echo "$TARGET_HOSTNAME" > /mnt/root/etc/hostname

echo "[*] Installing boot menu and IP announcer..."
cp /workspace/bootmenu.sh /mnt/root/usr/local/bin/bootmenu.sh
chmod +x /mnt/root/usr/local/bin/bootmenu.sh
echo '/usr/local/bin/bootmenu.sh' >> /mnt/root/etc/profile

cp /workspace/ip_announce.py /mnt/root/usr/local/bin/ip_announce.py
chmod +x /mnt/root/usr/local/bin/ip_announce.py

cat > /mnt/root/etc/systemd/system/ip-announce.service <<EOF
[Unit]
Description=Announce IP on UDP discovery
After=network-online.target

[Service]
ExecStart=/usr/bin/python3 /usr/local/bin/ip_announce.py
Restart=always

[Install]
WantedBy=multi-user.target
EOF

ln -s /etc/systemd/system/ip-announce.service /mnt/root/etc/systemd/system/multi-user.target.wants/ip-announce.service

sync
umount /mnt/boot /mnt/root
losetup -d $LOOPDEV

mv "$BASE_IMG" output/pi_bootloader.img

echo "[\u2713] Bootloader image ready: output/pi_bootloader.img"
