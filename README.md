# shawly's ESPHome Components

This repository contains my personal and some customized default components for [ESPHome](https://esphome.io/).

## 1. Usage

Add the repository to [`external_components`](https://esphome.io/components/external_components.html) in your configuration like this.

```yaml
external_components:
  - source: github://shawly/esphome-components
```

## 2. Components

### 2.1. `uart`

This is a customized version of the uart component which allows the use of hardware flow control for ESP32 boards.  
**You can only use this with the [ESP-IDF framework](https://esphome.io/components/esp32.html#esp32-espidf-framework) and ESP32 boards!**

#### 2.1.1. Example

```yaml
# required
external_components:
  - source: github://shawly/esphome-components
    components: [uart]

esp32:
  board: esp32dev
  framework:
    # this is also required
    type: esp-idf
    version: recommended
    sdkconfig_options:
      CONFIG_COMPILER_OPTIMIZATION_SIZE: y

uart:
  tx_pin: GPIO21
  rx_pin: GPIO19
  baud_rate: 57600
  # you need to set rts & cts pins
  rts_pin: GPIO18
  cts_pin: GPIO5
  # possible values are
  # - DISABLE = disable hardware flow control
  # - RTS = enable RX hardware flow control (rts)
  # - CTS = enable TX hardware flow control (cts)
  # - CTS_RTS = enable hardware flow control
  # - MAX = ?
  hw_flowctrl: CTS_RTS
  debug:
    # this is just for debugging
    direction: BOTH
    dummy_receiver: true
    after:
      delimiter: "\n"
    sequence:
      - lambda: UARTDebug::log_string(direction, bytes);

switch:
  - platform: uart
    name: "UART Test"
    data: "Hello World\n"
```

#### 2.1.2. Notes

To test hardware flow control you need a USB to TTL serial adapter with an FTDI FT232RL chip which allows you to use hardware flow control. It should have pins for RTS and CTS.  
These ones should work: [[1](https://www.amazon.com/dp/B07BBPX8B8)] (confirmed working) [[2](https://www.amazon.com/dp/B07XF2SLQ1)] (this one requires soldering pin headers for RTS/CTS)  
Remember to enable hardware flow control on your host with `stty -F /dev/ttyUSB0 crtscts` and don't forget to set the correct baudrate with `stty -F /dev/ttyUSB0 57600` (replace 57600 with your required baudrate)
