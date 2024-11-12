#include <Wire.h>
#include <DS3231.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUMPIXELS 24

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
RTClib myRTC;

uint32_t green = strip.Color(0, 255, 0);
uint32_t red = strip.Color(255, 0, 0);
uint32_t blue = strip.Color(0, 0, 255);
uint32_t white = strip.Color(255, 255, 255);

uint32_t initialColors[NUMPIXELS];

void setInitialColors() {
  strip.clear();
  strip.setPixelColor(0, green);
  initialColors[0] = green;
  strip.setPixelColor(11, green);
  initialColors[11] = green;

  int redDiods[] = {1, 3, 5, 7, 9, 13, 15, 17, 19, 21, 23};
  for (int i = 0; i < 11; i++) {
    strip.setPixelColor(redDiods[i], red);
    initialColors[redDiods[i]] = red;
  }

  int blueDiods[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22};
  for (int i = 0; i < 11; i++) {
    strip.setPixelColor(blueDiods[i], blue);
    initialColors[blueDiods[i]] = blue;
  }

  strip.show();
}

void rouletteAnimation(uint8_t initialSpeed, uint8_t rounds, int stopPosition) {
  int currentPos = 0;
  int totalSteps = NUMPIXELS * rounds + stopPosition;
  uint8_t speed = initialSpeed;

  for (int step = 0; step < totalSteps; step++) {
    for (int j = 0; j < NUMPIXELS; j++) {
      strip.setPixelColor(j, initialColors[j]);
    }

    strip.setPixelColor(currentPos, white);
    strip.show();
    delay(speed);

    currentPos++;
    if (currentPos >= NUMPIXELS) {
      currentPos = 0;
    }

    if (step > totalSteps - NUMPIXELS) {
      speed += 5;
    }
  }
}

void setup() {
  strip.begin();
  strip.setBrightness(50);
  strip.show();
  Serial.begin(57600);
  Wire.begin();
  delay(500);

  setInitialColors();
}

void loop() {
  delay(2000);
  int winningNumber = getRandomNumber(24);
  int winningPos = winningNumber - 1;

  rouletteAnimation(50, 2, winningPos);

  strip.clear();
  strip.setPixelColor(winningPos, white);
  strip.show();
  delay(1000);

  uint32_t colorToSet = initialColors[winningPos];
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, colorToSet);
  }
  strip.show();

  delay(5000);

  strip.clear();
  strip.show();
  delay(5000);
}

int getRandomNumber(int max) {
  return random(1, max + 1);
}
