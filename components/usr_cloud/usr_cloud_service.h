//
// Created by Lay on 7/21/2023.
//

#ifndef SILLY_IOT_FARM_V2_USR_CLOUD_SERVICE_H
#define SILLY_IOT_FARM_V2_USR_CLOUD_SERVICE_H

#include <esp_rmaker_core.h>

namespace usr {
    extern esp_rmaker_device_t *sensor_temp;
    extern esp_rmaker_device_t *sensor_humidity;
    extern esp_rmaker_device_t *sensor_pressure;
    extern esp_rmaker_device_t *sensor_light;
    extern esp_rmaker_device_t *switch_light;
    extern esp_rmaker_device_t *switch_water;
    extern esp_rmaker_device_t *switch_mode;
    extern esp_rmaker_param_t *light_power;
    extern esp_rmaker_param_t *water_power;
    extern esp_rmaker_param_t *auto_mode_power;
    extern esp_rmaker_param_t *light_red;
    extern esp_rmaker_param_t *light_green;
    extern esp_rmaker_param_t *light_blue;
    extern esp_rmaker_param_t *temperature_value;
    extern esp_rmaker_param_t *humidity_value;
    extern esp_rmaker_param_t *pressure_value;
    extern esp_rmaker_param_t *light_cct_value;
    extern esp_rmaker_param_t *light_wavelength_value;
    extern esp_rmaker_param_t *light_lux_value;

    void rainmaker_init();
}
#endif //SILLY_IOT_FARM_V2_USR_CLOUD_SERVICE_H
