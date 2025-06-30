#!/bin/bash
set -euo pipefail

IMG_NAME="raspios_lite_custom.img"
ZIP_NAME="raspios_lite_64_latest.zip"
RPI_OS_URL="https://downloads.raspberrypi.org/raspios_lite_arm64_latest"
WORKDIR=$(pwd)
OUTDIR="$WORKDIR/output"

mkdir -p "$OUTDIR"

echo "[*] Downloading Raspberry Pi OS Lite 64-bit..."
wget -qO "$OUTDIR/$ZIP_NAME" "$RPI_OS_URL"

echo "[*] Extracting image..."
unzip -o "$OUTDIR/$ZIP_NAME" -d "$OUTDIR"
IMG_ORIG=$(find "$OUTDIR" -name "*.img" | head -n1)

cp "$IMG_ORIG" "$OUTDIR/$IMG_NAME"

echo "[*] Setting up loop device..."
LOOPDEV=$(losetup --show -fP "$OUTDIR/$IMG_NAME")

# Wait briefly to ensure partitions are mapped
sleep 1

MNT_BOOT="$WORKDIR/mnt_boot"
mkdir -p "$MNT_BOOT"
mount "${LOOPDEV}p1" "$MNT_BOOT"

echo "[*] Enabling SSH..."
touch "$MNT_BOOT/ssh"

echo "[*] Adding Wi-Fi config..."
cat > "$MNT_BOOT/wpa_supplicant.conf" <<EOF
ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
country=US

network={
    ssid="$WIFI_SSID"
    psk="$WIFI_PASS"
}
EOF

echo "[*] Setting hostname..."
ROOT_PART="${LOOPDEV}p2"
MNT_ROOT="$WORKDIR/mnt_root"
mkdir -p "$MNT_ROOT"
mount "$ROOT_PART" "$MNT_ROOT"
echo "$HOSTNAME" > "$MNT_ROOT/etc/hostname"

echo "[*] Cleaning up..."
sync
umount "$MNT_BOOT"
umount "$MNT_ROOT"
losetup -d "$LOOPDEV"

echo "[✓] Customized image created at: $OUTDIR/$IMG_NAME"
