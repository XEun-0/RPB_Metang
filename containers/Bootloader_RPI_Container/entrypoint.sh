#!/bin/bash
set -e

# You can override these with environment variables
export WIFI_SSID=${WIFI_SSID:-"YourSSID"}
export WIFI_PASS=${WIFI_PASS:-"YourPassword"}
export HOSTNAME=${HOSTNAME:-"rpi-custom"}

./customize_rpi_os.sh
