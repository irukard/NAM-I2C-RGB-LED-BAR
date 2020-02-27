# Nettigo Air Monitor I2C RGB LED Bar

Firmware for I2C Slave RGB LED BAR based on Neopixel LEDs.

## Hardware
This firmware is written with [Nettigo Air Monitor 0.3 I2C RGB LED Bar](https://easyeda.com/nettigo/Nettigo-Air-Monitor-I2C-RGB-LED-Bar) in mind.

Device is based on ATtiny84A with ten WS2812E Neopixel LEDs. It meant to be a slave I2C device driving Neopixels acordingly to recived commands from I2C master. To make it 3V3 compatible board itself doesn't have I2C pullups (and since I2C is open drain it doesn't change logic level during communication). ATtiny84A is powered from 5V rail to ensure propper logic level in communication with LEDs.

### Wiring

- I2C_SDA - PIN4 - PA6 (PCINT6/OC1A/SDA/MOSI/DI/ADC6)
- I2C_SCL - PIN6 - PA4 (PCINT4/T1/SCL/USCK/ADC4)
- WS2812E - PIN10 - PA0 (PCINT1/AIO0/ADC1)