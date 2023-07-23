//
// Created by Lay on 5/4/2023.
//

#ifndef SILLY_IOT_FARM_USR_LIGHT_H
#define SILLY_IOT_FARM_USR_LIGHT_H

#include "ws2812_control.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"


namespace usr {
    struct color_t {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
        uint8_t white;
    };
    extern xQueueHandle light_queue;

    esp_err_t light_task_create();
}
#endif //SILLY_IOT_FARM_USR_LIGHT_H
