/**
 * @file button.ino
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
}

void loop() {
    NanoC6.update();
    if (NanoC6.BtnA.wasPressed()) {
        Serial.println("Button A was pressed");
    }
    if (NanoC6.BtnA.wasHold()) {
        Serial.println("Button A was hold");
    }
    if (NanoC6.BtnA.wasReleased()) {
        Serial.println("Button A was released");
    }
}
