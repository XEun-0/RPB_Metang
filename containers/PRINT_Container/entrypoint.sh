#!/bin/bash

# Start CUPS
service cups start

# Wait for USB device
sleep 5

# Detect printer (example URI: usb://HP/LaserJet%20P1102w)
PRINTER_URI=$(lpinfo -v | grep -i HP | awk '{print $3}' | head -n 1)

if [ -n "$PRINTER_URI" ]; then
  echo "Printer detected at $PRINTER_URI"
  lpadmin -p HP_Printer -E -v "$PRINTER_URI" -m everywhere
  lpoptions -d HP_Printer
else
  echo "No HP printer found."
fi

# Keep container running
tail -f /dev/null
