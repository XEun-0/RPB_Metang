#!/bin/bash
set -e

DEVICE="/dev/mmcblk0"

# Check if partition 3 exists, create if not
if ! ls ${DEVICE}p3 &>/dev/null; then
  echo "[*] Creating new partition..."
  parted $DEVICE --script mkpart primary ext4 1000MiB 100%
  partprobe $DEVICE
  mkfs.ext4 ${DEVICE}p3
  echo "[✓] New partition created and formatted"
else
  echo "[*] Partition 3 already exists, skipping partitioning"
fi

# Optionally mount or use the partition here

# Disable this service so it runs once only
systemctl disable partition-sd.service
