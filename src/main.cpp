#include <Arduino.h>
#include <tinyNeoPixel.h>
#include <TinyWireS.h>

#define NEOPIN 10               // NeoPixel Pin
#define NEONUM 10               // Number of pixels
#define I2C_SLAVE_ADDRESS 0x32  // I2C Slave Address

tinyNeoPixel pixels = tinyNeoPixel(NEONUM, NEOPIN, NEO_GRB + NEO_KHZ800);

#ifndef TWI_RX_BUFFER_SIZE
#define TWI_RX_BUFFER_SIZE ( 4 )
#endif

// The "registers" we expose to I2C
volatile uint8_t i2c_regs[] =
        {
                0x0,
                0x0,
                0x1,
                0x0,
        };
const byte reg_size = sizeof(i2c_regs);
// Tracks the current register pointer position
volatile byte reg_position=0;

/**
 * This is called for each read request we receive, never put more than one byte of data (with TinyWireS.send) to the
 * send-buffer when using this callback
 */
void requestEvent() {
    TinyWireS.send(NEONUM);
}

/**
 * The I2C data received -handler
 *
 * This needs to complete before the next incoming transaction (start, data, restart/stop) on the bus does
 * so be quick, set flags for long running tasks to be called from the mainloop instead of running them directly,
 */
void receiveEvent(uint8_t howMany) {
    if (howMany < 1) {
        // Sanity-check
        return;
    }
    if (howMany > TWI_RX_BUFFER_SIZE) {
        // Also insane number
        return;
    }

    while (howMany--) {
        i2c_regs[reg_position] = TinyWireS.receive();
//        if (reg_position == 0 // If it was the first register
//            && bitRead(i2c_regs[0], 7) // And the highest bit is set
//            && !ADC_ConversionInProgress() // and we do not actually have a conversion running already
//                ) {
//            start_conversion = true;
//        }
        reg_position++;
        if (reg_position >= reg_size) {
            reg_position = 0;
        }
    }
    return;
}

void setup() {
    pixels.begin();
    // Neopixel Test Run
    for (byte i = 0; i < NEONUM; i++) {
        pixels.setPixelColor(i, pixels.Color(30,0,0));
        pixels.show();
        delay(25);
    }
    for (byte i = NEONUM; i >= 0; i--) {
        pixels.setPixelColor(i, pixels.Color(0,0,0));
        pixels.show();
        delay(25);
    }
    TinyWireS.begin(I2C_SLAVE_ADDRESS);
    TinyWireS.onReceive(receiveEvent);
    TinyWireS.onRequest(requestEvent);
    

}

void loop() {

    byte r = i2c_regs[1];
    byte g = i2c_regs[2];
    byte b = i2c_regs[3];
    byte cnt = i2c_regs[0];

    for (byte i = 0; i < cnt; i++) {
        pixels.setPixelColor(i, pixels.Color(r,g,b));
    }

    for (byte i = cnt; i < NEONUM; i++) {
        pixels.setPixelColor(i, pixels.Color(0,0,0));
    }
    pixels.show();
    tws_delay(10); // Wait 500 ms
//    TinyWireS_stop_check();
    return;
}