#!/bin/bash
# Quick script to set env & build for xiao_esp32s3

source ../zephyrproject/.venv/bin/activate
source ../zephyrproject/zephyr/zephyr-env.sh
source ../zephyrproject/zephyr/scripts/west_commands/completion/west-completion.bash

west build -p always -b xiao_esp32s3/esp32s3/procpu
export ESPTOOL_PORT=/dev/ttyACM0
west flash
west espressif monitor -p /dev/ttyACM0