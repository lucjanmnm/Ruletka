# LED Roulette Game

This project is a simple LED roulette game using an Arduino, an Adafruit NeoPixel strip. The roulette animation will randomly stop on one of the LEDs and light it up in a white color before changing all LEDs to the same color as the winning LED.

## Components Required

- Arduino (Uno, Nano, etc.)
- Adafruit NeoPixel LED strip (24 LEDs)
- Connecting wires
- Breadboard (optional)

## Circuit Diagram

1. Connect the NeoPixel LED strip to the Arduino:
   - DIN to digital pin 6
   - VCC to 5V
   - GND to GND

### Libraries

Ensure you have the Adafruit_NeoPixel, DS3221 and RTClib libraries installed. You can install these via the Arduino Library Manager.

### Code

Upload the provided Arduino code to your Arduino board.
