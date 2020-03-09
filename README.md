# Nettigo Air Monitor I2C RGB LED Bar

Firmware for I2C Slave RGB LED BAR based on Neopixel LEDs.

## Hardware
This firmware is written with [Nettigo Air Monitor 0.3 I2C RGB LED Bar](https://easyeda.com/nettigo/Nettigo-Air-Monitor-I2C-RGB-LED-Bar) in mind.

Device is based on ATtiny84A with ten WS2812 Neopixel LEDs. It meant to be a slave I2C device driving Neopixels acordingly to recived commands from I2C master. To make it 3V3 compatible board itself doesn't have I2C pullups (and since I2C is open drain it doesn't change logic level during communication). ATtiny84A is powered from 5V rail to ensure propper logic level in communication with LEDs.

### Wiring

- I2C_SDA - PIN4 - PA6 (PCINT6/OC1A/SDA/MOSI/DI/ADC6)
- I2C_SCL - PIN6 - PA4 (PCINT4/T1/SCL/USCK/ADC4)
- WS2812 - PIN10 - PA0 (PCINT1/AIO0/ADC1)

### Programming

Device can be programmed with cheap USBASP ICSP programmer with 6-pin adapter (eg. [NAR-307](https://nettigo.eu/products/usbasp-icsp-programmer) + [NAR-894](https://nettigo.eu/products/10pin-to-6-pin-isp-adapter-for-avr-programming)). In case of fresh ATtiny84A chip straight from factory, don't forget to burn fusebits. 

### Protocol

Communication protocol is as simple as it can be. Start transmition with correct address, send 5 bytes: mode, count, red, green, blue and stop transmission.

Example master code:

    void lightLED(byte mode, byte cnt, byte red, byte green, byte blue) {
        Wire.beginTransmission(LED_BAR_ADDRESS); // transmit to device, default 0x32
        Wire.write(mode);
        Wire.write(cnt);
        Wire.write(red);
        Wire.write(green);
        Wire.write(blue);
        Wire.endTransmission();    // stop transmitting
    }

- Mode 0: Light up fist n (acording to cnt) LEDs with RGB colour. LEDs above n will be turned off.
- Mode 1: Change colour of single LED with RGB values. The rest will stay the same.

If you request information from device, it will return number of LEDs in slave device.