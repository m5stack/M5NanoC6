/**
 * @file rgb_led.ino
 * @author SeanKwok (shaoxiang@m5stack.com)
 * @brief
 * @version 0.1
 * @date 2024-03-19
 *
 *
 * @Hardwares: M5NanoC6
 * @Platform Version: Arduino ESP32 Board Manager v3.0.0-alpha3
 * @Dependent Library:
 * M5NanoC6: https://github.com/m5stack/M5NanoC6
 * Adafruit_NeoPixel: https://github.com/adafruit/Adafruit_NeoPixel
 */

#include "M5NanoC6.h"
#include <Adafruit_NeoPixel.h>

#define NUM_LEDS 1
Adafruit_NeoPixel strip(NUM_LEDS, M5NANO_C6_RGB_LED_DATA_PIN,
                        NEO_GRB + NEO_KHZ800);

void setup() {
    // Enable RGB LED Power
    pinMode(M5NANO_C6_RGB_LED_PWR_PIN, OUTPUT);
    digitalWrite(M5NANO_C6_RGB_LED_PWR_PIN, HIGH);

    strip.begin();
    strip.show();
}

void loop() {
    strip.setPixelColor(0, strip.Color(255, 0, 0));
    strip.show();
    delay(100);

    strip.setPixelColor(0, strip.Color(0, 255, 0));
    strip.show();
    delay(100);

    // 蓝色
    strip.setPixelColor(0, strip.Color(0, 0, 255));
    strip.show();
    delay(100);
}
