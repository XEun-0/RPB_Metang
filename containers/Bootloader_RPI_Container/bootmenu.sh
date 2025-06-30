#!/bin/bash

clear
while true; do
  echo "=============================="
  echo "   Raspberry Pi Bootloader    "
  echo "=============================="
  echo "1. Flash new OS image to /dev/mmcblk0p2"
  echo "2. Reboot into OS partition"
  echo "3. Wipe OS partition"
  echo "4. Exit to shell"
  echo "=============================="
  read -p "Select option [1-4]: " option

  case $option in
    1)
      echo "Searching for /home/pi/new_os.img..."
      if [ -f /home/pi/new_os.img ]; then
        echo "Flashing image to /dev/mmcblk0p2..."
        dd if=/home/pi/new_os.img of=/dev/mmcblk0p2 bs=4M status=progress
        echo "Done."
      else
        echo "File not found. Upload using:"
        echo "scp new_os.img pi@<ip>:/home/pi/"
      fi
      read -p "Press Enter to return to menu..." ;;
    2)
      echo "Rebooting into OS partition..."
      sed -i 's/mmcblk0p1/mmcblk0p2/' /boot/cmdline.txt
      reboot ;;
    3)
      echo "Wiping partition..."
      mkfs.ext4 /dev/mmcblk0p2
      echo "Done."
      read -p "Press Enter to return to menu..." ;;
    4)
      echo "Exiting..."
      break ;;
    *)
      echo "Invalid option."
      sleep 1 ;;
  esac
done
