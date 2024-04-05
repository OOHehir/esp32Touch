# esp32Blink
Simple 'out of tree' project to test touch feature on the ESP32 S3 using the Zephyr RTOS
## Init:
```
    source ../zephyrproject/.venv/bin/activate
    source ../zephyrproject/zephyr/zephyr-env.sh
    source ../zephyrproject/zephyr/scripts/west_commands/completion/west-completion.bash
```
## Build:
Build application & bootloader
```
    west build -p always -b xiao_esp32s3
```
## Binary blobs
Espressif HAL requires WiFi and Bluetooth binary blobs in order work. Run the command below to retrieve those files.
```
west blobs fetch hal_espressif
```
## Flash
```
    west flash
```
## Pinout:

![ESP32S3](screenshots/esp32s3_pinout.jpeg)