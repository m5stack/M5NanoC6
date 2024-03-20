#include "M5NanoC6.h"

using namespace m5;

M5NanoC6 NanoC6;

void M5NanoC6::begin() {
    Serial.begin(115200);
    pinMode(M5NANO_C6_BTN_PIN, INPUT);
}

void M5NanoC6::update(void) {
    uint32_t ms = millis();
    BtnA.setRawState(ms, !digitalRead(M5NANO_C6_BTN_PIN));
}