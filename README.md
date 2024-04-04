# esp32Blink
Simple 'out of tree' project to test touch on the ESP32 S3 using the Zephyr RTOS

### Building and Running

This application can be built and executed on QEMU as follows:

#### Init:
```
    source ../zephyrproject/.venv/bin/activate
    source ../zephyrproject/zephyr/zephyr-env.sh
    source ../zephyrproject/zephyr/scripts/west_commands/completion/west-completion.bash
```

#### Build:
```
    west build -p always -b qemu_x86
```

To build for another board, change "qemu_x86" above to that board's name.

### Sample Output

```
    Hello World! x86
```

Exit QEMU by pressing `CTRL+A`
