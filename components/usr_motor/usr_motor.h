//
// Created by Lay on 5/4/2023.
//

#ifndef SILLY_IOT_FARM_USR_MOTOR_H
#define SILLY_IOT_FARM_USR_MOTOR_H

#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

namespace usr {
    extern SemaphoreHandle_t motor_semaphr;
    extern xQueueHandle motor_queue;

    esp_err_t motor_task_create();
}

#endif //SILLY_IOT_FARM_USR_MOTOR_H
