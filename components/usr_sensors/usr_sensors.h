
//
// Created by Lay on 5/4/2023.
//

#ifndef SILLY_IOT_FARM_USR_SENSORS_H
#define SILLY_IOT_FARM_USR_SENSORS_H

#include "iot_sensor_hub.h"

namespace usr {
    struct light_data_t {
        float wave_length;
        float ambient_light_Lux;
        float cct;
        rgbw_t light_rgbw;
    };
    struct sensor_data_t {
        float humidity;
        float temperature;
        float pressure;
        light_data_t light_data;
//        uv_t light_uv;
    };
    extern xQueueHandle sensor_data_queue;

    esp_err_t sensors_task_create();

    esp_err_t sensors_gui_test();
}
#endif //SILLY_IOT_FARM_USR_SENSORS_H
