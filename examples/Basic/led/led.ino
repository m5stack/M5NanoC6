/**
 * @file led.ino
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
 */

#include "M5NanoC6.h"

void setup() {
    NanoC6.begin();
    pinMode(M5NANO_C6_BLUE_LED_PIN, OUTPUT);
}

void loop() {
    digitalWrite(M5NANO_C6_BLUE_LED_PIN, HIGH);
    delay(1000);
    digitalWrite(M5NANO_C6_BLUE_LED_PIN, LOW);
    delay(1000);
}
