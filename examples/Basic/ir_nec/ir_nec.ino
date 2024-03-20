/**
 * @file ir_nec.ino
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
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "driver/rmt_tx.h"
#include "driver/rmt_rx.h"
#include "driver/gpio.h"

#define EXAMPLE_IR_RESOLUTION_HZ 1000000  // 1MHz resolution, 1 tick = 1us
#define EXAMPLE_IR_NEC_DECODE_MARGIN \
    200  // Tolerance for parsing RMT symbols into bit stream

rmt_encoder_handle_t nec_encoder = NULL;
uint16_t ir_addr                 = 0x0440;
uint16_t ir_cmd                  = 0x0000;

// Function to generate NEC IR code
void ir_send(uint16_t addr, uint16_t cmd) {
    rmt_data_t rmt_data[2 + 16 + 16];

    // Start pulse
    rmt_data[0] = {
        .duration0 = 9000ULL * EXAMPLE_IR_RESOLUTION_HZ / 1000000,
        .level0    = 1,
        .duration1 = 4500ULL * EXAMPLE_IR_RESOLUTION_HZ / 1000000,
        .level1    = 0,
    };
    int index = 1;

    uint8_t addrLowByte  = addr & 0xFF;
    uint8_t addrHighByte = (addr >> 8) & 0xFF;
    uint8_t cmdLowByte   = cmd & 0xFF;
    uint8_t cmdHighByte  = (cmd >> 8) & 0xFF;

    // Address transmission
    for (int8_t i = 0; i < 8; ++i) {
        if (addrLowByte & (1 << i)) {  // If bit is 1
            rmt_data[index] = {
                .duration0 = 560ULL * EXAMPLE_IR_RESOLUTION_HZ / 1000000,
                .level0    = 1,
                .duration1 = 1690ULL * EXAMPLE_IR_RESOLUTION_HZ / 1000000,
                .level1    = 0,
            };
        } else {  // If bit is 0
            rmt_data[index] = {
                .duration0 = 560ULL * EXAMPLE_IR_RESOLUTION_HZ / 1000000,
                .level0    = 1,
                .duration1 = 560ULL * EXAMPLE_IR_RESOLUTION_HZ / 1000000,
                .level1    = 0,
            };
        }
        index++;
    }

    // Address transmission
    for (int8_t i = 0; i < 8; ++i) {
        if (addrHighByte & (1 << i)) {  // If bit is 1
            rmt_data[index] = {
                .duration0 = 560ULL * EXAMPLE_IR_RESOLUTION_HZ / 1000000,
                .level0    = 1,
                .duration1 = 1690ULL * EXAMPLE_IR_RESOLUTION_HZ / 1000000,
                .level1    = 0,
            };
        } else {  // If bit is 0
            rmt_data[index] = {
                .duration0 = 560ULL * EXAMPLE_IR_RESOLUTION_HZ / 1000000,
                .level0    = 1,
                .duration1 = 560ULL * EXAMPLE_IR_RESOLUTION_HZ / 1000000,
                .level1    = 0,
            };
        }
        index++;
    }

    // Command transmission
    for (int8_t i = 0; i < 8; ++i) {
        if (cmdLowByte & (1 << i)) {  // If bit is 1
            rmt_data[index] = {
                .duration0 = 560ULL * EXAMPLE_IR_RESOLUTION_HZ / 1000000,
                .level0    = 1,
                .duration1 = 1690ULL * EXAMPLE_IR_RESOLUTION_HZ / 1000000,
                .level1    = 0,
            };
        } else {  // If bit is 0
            rmt_data[index] = {
                .duration0 = 560ULL * EXAMPLE_IR_RESOLUTION_HZ / 1000000,
                .level0    = 1,
                .duration1 = 560ULL * EXAMPLE_IR_RESOLUTION_HZ / 1000000,
                .level1    = 0,
            };
        }
        index++;
    }

    // uint8_t cmdLowByteReverse = ~cmdLowByte;
    // Command transmission
    for (int8_t i = 0; i < 8; ++i) {
        if (cmdHighByte & (1 << i)) {  // If bit is 1
            rmt_data[index] = {
                .duration0 = 560ULL * EXAMPLE_IR_RESOLUTION_HZ / 1000000,
                .level0    = 1,
                .duration1 = 1690ULL * EXAMPLE_IR_RESOLUTION_HZ / 1000000,
                .level1    = 0,
            };
        } else {  // If bit is 0
            rmt_data[index] = {
                .duration0 = 560ULL * EXAMPLE_IR_RESOLUTION_HZ / 1000000,
                .level0    = 1,
                .duration1 = 560ULL * EXAMPLE_IR_RESOLUTION_HZ / 1000000,
                .level1    = 0,
            };
        }
        index++;
    }

    // end pulse
    rmt_data[index] = {
        .duration0 = 560ULL * EXAMPLE_IR_RESOLUTION_HZ / 1000000,
        .level0    = 1,
        .duration1 = 0x7FFF,
        .level1    = 0,
    };
    rmtWrite(M5NANO_C6_IR_TX_PIN, rmt_data, 2 + 16 + 16, RMT_WAIT_FOR_EVER);
}

void setup() {
    NanoC6.begin();
    // init IR TX
    ir_init();
}

void loop() {
    ir_send(ir_addr, ir_cmd++);
    Serial.printf("IR: %04X:%04X\r\n", ir_addr, ir_cmd);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
}

void ir_init() {
    rmtInit(M5NANO_C6_IR_TX_PIN, RMT_TX_MODE, RMT_MEM_NUM_BLOCKS_2,
            EXAMPLE_IR_RESOLUTION_HZ);
    rmtSetCarrier(M5NANO_C6_IR_TX_PIN, true, LOW, 38000, 0.33);
}
