//
// Created by Lay on 7/21/2023.
//

#include "usr_cloud_service.h"
#include <nvs_flash.h>
#include <esp_rmaker_core.h>
#include <esp_rmaker_standard_params.h>
#include <esp_rmaker_standard_devices.h>
#include "esp_rmaker_scenes.h"
#include "esp_rmaker_schedule.h"
#include <app_wifi.h>
#include <app_insights.h>
#include <cstring>
#include "usr_light.h"
#include "usr_motor.h"
#include "esp_lvgl_port.h"
#include "ui.h"
#include "esp_log.h"

namespace usr {
    static const char *TAG = "rainmaker";
    esp_rmaker_node_t *node;
    esp_rmaker_device_t *sensor_temp;
    esp_rmaker_device_t *sensor_humidity;
    esp_rmaker_device_t *sensor_pressure;
    esp_rmaker_device_t *sensor_light;
    esp_rmaker_device_t *switch_light;
    esp_rmaker_device_t *switch_water;
    esp_rmaker_device_t *switch_mode;
    esp_rmaker_param_t *light_power;
    esp_rmaker_param_t *water_power;
    esp_rmaker_param_t *auto_mode_power;
    esp_rmaker_param_t *light_red;
    esp_rmaker_param_t *light_green;
    esp_rmaker_param_t *light_blue;
    esp_rmaker_param_t *temperature_value;
    esp_rmaker_param_t *humidity_value;
    esp_rmaker_param_t *pressure_value;
    esp_rmaker_param_t *light_cct_value;
    esp_rmaker_param_t *light_wavelength_value;
    esp_rmaker_param_t *light_lux_value;
    static int light_r_val = 127, light_g_val = 127, light_b_val = 127;
    static bool light_on = false;

    static esp_err_t write_cb(const esp_rmaker_device_t *device, const esp_rmaker_param_t *param,
                              const esp_rmaker_param_val_t val, void *priv_data, esp_rmaker_write_ctx_t *ctx) {
        const char *device_name = esp_rmaker_device_get_name(device);
        const char *param_name = esp_rmaker_param_get_name(param);
        if (strcmp(device_name, "补光") == 0) {
            if (strcmp(param_name, "红") == 0) { light_r_val = val.val.i; }
            else if (strcmp(param_name, "绿") == 0) { light_g_val = val.val.i; }
            else if (strcmp(param_name, "蓝") == 0) { light_b_val = val.val.i; }
            else if (strcmp(param_name, ESP_RMAKER_DEF_POWER_NAME) == 0) { light_on = val.val.b; }
            //if power on,then send color command
            usr::color_t color_cmd{0, 0, 0, 0};
            if (light_on) {
                color_cmd = {.red=uint8_t(light_r_val), .green=uint8_t(light_g_val), .blue=uint8_t(light_b_val)};
                lvgl_port_lock(0);
                lv_obj_add_state(light_Switch, LV_STATE_CHECKED);
                lvgl_port_unlock();
            } else {
                lvgl_port_lock(0);
                lv_obj_clear_state(light_Switch, LV_STATE_CHECKED);
                lvgl_port_unlock();
            }
            xQueueSend(usr::light_queue, &color_cmd, pdMS_TO_TICKS(5));
        } else if (strcmp(device_name, "浇水") == 0) {
            if (strcmp(param_name, ESP_RMAKER_DEF_POWER_NAME) == 0) {
                int motor_level = val.val.b ? 1 : 0;
                if (motor_level) {
                    lvgl_port_lock(0);
                    lv_obj_add_state(water_Switch, LV_STATE_CHECKED);
                    lvgl_port_unlock();
                } else {
                    lvgl_port_lock(0);
                    lv_obj_clear_state(water_Switch, LV_STATE_CHECKED);
                    lvgl_port_unlock();
                }
                xQueueSend(usr::motor_queue, &motor_level, pdMS_TO_TICKS(5));
            }
        }
//        } else if (strcmp(device_name, "专家模式") == 0) {
//            if (strcmp(param_name, ESP_RMAKER_DEF_POWER_NAME) == 0) {
//                if (val.val.b) {
//                    lvgl_port_lock(0);
//                    lv_obj_add_state(auto_mode_Switch, LV_STATE_CHECKED);
//                    lvgl_port_unlock();
//                } else {
//                    lvgl_port_lock(0);
//                    lv_obj_clear_state(auto_mode_Switch, LV_STATE_CHECKED);
//                    lvgl_port_unlock();
//                }
//            }
//        }
        return ESP_OK;
    }

    static void rmaker_add_devices() {
        /***********************************sensors*******************************/
        sensor_temp = esp_rmaker_device_create("温度传感器", nullptr, nullptr);
        sensor_humidity = esp_rmaker_device_create("湿度传感器", nullptr, nullptr);
        sensor_pressure = esp_rmaker_device_create("压强传感器", nullptr, nullptr);
        sensor_light = esp_rmaker_device_create("环境光传感器", nullptr, nullptr);

        temperature_value = esp_rmaker_param_create("温度", nullptr, esp_rmaker_float(0.0f),
                                                    PROP_FLAG_READ);
        humidity_value = esp_rmaker_param_create("湿度", nullptr, esp_rmaker_float(0.0f),
                                                 PROP_FLAG_READ);
        pressure_value = esp_rmaker_param_create("压强", nullptr, esp_rmaker_float(0.0f),
                                                 PROP_FLAG_READ);
        light_cct_value = esp_rmaker_param_create("色温cct", nullptr, esp_rmaker_float(0.0f), PROP_FLAG_READ);
        light_wavelength_value = esp_rmaker_param_create("波长", nullptr, esp_rmaker_float(0.0f),
                                                         PROP_FLAG_READ);
        light_lux_value = esp_rmaker_param_create("光强lux", nullptr, esp_rmaker_float(0.0f),
                                                  PROP_FLAG_READ);
        esp_rmaker_device_add_param(sensor_temp, temperature_value);
        esp_rmaker_device_assign_primary_param(sensor_temp, temperature_value);
        esp_rmaker_device_add_param(sensor_humidity, humidity_value);
        esp_rmaker_device_assign_primary_param(sensor_humidity, humidity_value);
        esp_rmaker_device_add_param(sensor_pressure, pressure_value);
        esp_rmaker_device_assign_primary_param(sensor_pressure, pressure_value);
        esp_rmaker_device_add_param(sensor_light, light_cct_value);
        esp_rmaker_device_add_param(sensor_light, light_wavelength_value);
        esp_rmaker_device_add_param(sensor_light, light_lux_value);
        esp_rmaker_device_assign_primary_param(sensor_light, light_lux_value);
        /***********************************switches*******************************/
        switch_light = esp_rmaker_switch_device_create("补光", nullptr, false);
        switch_water = esp_rmaker_switch_device_create("浇水", nullptr, false);
//        switch_mode = esp_rmaker_switch_device_create("专家模式", nullptr, false);
        light_power = esp_rmaker_device_get_param_by_name(switch_light, ESP_RMAKER_DEF_POWER_NAME);
        water_power = esp_rmaker_device_get_param_by_name(switch_water, ESP_RMAKER_DEF_POWER_NAME);
//        auto_mode_power = esp_rmaker_device_get_param_by_name(switch_mode, ESP_RMAKER_DEF_POWER_NAME);
        light_red = esp_rmaker_param_create("红", nullptr, esp_rmaker_int(127),
                                            PROP_FLAG_READ | PROP_FLAG_WRITE);
        esp_rmaker_param_add_bounds(light_red, esp_rmaker_int(0), esp_rmaker_int(255), esp_rmaker_int(1));
        esp_rmaker_param_add_ui_type(light_red, "esp.ui.slider");
        light_green = esp_rmaker_param_create("绿", nullptr, esp_rmaker_int(127),
                                              PROP_FLAG_READ | PROP_FLAG_WRITE);
        esp_rmaker_param_add_bounds(light_green, esp_rmaker_int(0), esp_rmaker_int(255), esp_rmaker_int(1));
        esp_rmaker_param_add_ui_type(light_green, "esp.ui.slider");
        light_blue = esp_rmaker_param_create("蓝", nullptr, esp_rmaker_int(127),
                                             PROP_FLAG_READ | PROP_FLAG_WRITE);
        esp_rmaker_param_add_bounds(light_blue, esp_rmaker_int(0), esp_rmaker_int(255), esp_rmaker_int(1));
        esp_rmaker_param_add_ui_type(light_blue, "esp.ui.slider");

        esp_rmaker_device_add_param(switch_light, light_red);
        esp_rmaker_device_add_param(switch_light, light_green);
        esp_rmaker_device_add_param(switch_light, light_blue);
        esp_rmaker_device_add_cb(switch_light, write_cb, nullptr);
        esp_rmaker_device_add_cb(switch_water, write_cb, nullptr);
//        esp_rmaker_device_add_cb(switch_mode, write_cb, nullptr);

        esp_rmaker_node_add_device(node, sensor_light);
        esp_rmaker_node_add_device(node, sensor_pressure);
        esp_rmaker_node_add_device(node, sensor_humidity);
        esp_rmaker_node_add_device(node, sensor_temp);
        esp_rmaker_node_add_device(node, switch_light);
        esp_rmaker_node_add_device(node, switch_water);
//        esp_rmaker_node_add_device(node, switch_mode);
    }

    void rainmaker_init() {
        /* Initialize NVS. */
//        nvs_flash_erase();
        esp_err_t err = nvs_flash_init();
        if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
            ESP_ERROR_CHECK(nvs_flash_erase());
            err = nvs_flash_init();
        }
        ESP_ERROR_CHECK(err);

        /* Initialize Wi-Fi. Note that, this should be called before esp_rmaker_node_init()
         */
        app_wifi_init();

        /* Initialize the ESP RainMaker Agent.
         * Note that this should be called after app_wifi_init() but before app_wifi_start()
         * */
        esp_rmaker_config_t rainmaker_cfg = {
                .enable_time_sync = false,
        };
        node = esp_rmaker_node_init(&rainmaker_cfg, "IOT Farm", "SMART FARM");
        if (!node) {
            ESP_LOGE(TAG, "Could not initialise node. Aborting!!!");
            vTaskDelay(5000 / portTICK_PERIOD_MS);
            abort();
        }
        rmaker_add_devices();

        esp_rmaker_timezone_service_enable();
        /* Enable scheduling. */
        esp_rmaker_schedule_enable();

        /* Enable Scenes */
        esp_rmaker_scenes_enable();
        /* Enable Insights. Requires CONFIG_ESP_INSIGHTS_ENABLED=y */
        app_insights_enable();

        /* Start the ESP RainMaker Agent */
        esp_rmaker_start();

        /* Start the Wi-Fi.
         * If the node is provisioned, it will start connection attempts,
         * else, it will start Wi-Fi provisioning. The function will return
         * after a connection has been successfully established
         */
        err = app_wifi_start(POP_TYPE_RANDOM);
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "Could not start Wifi. Aborting!!!");
            vTaskDelay(5000 / portTICK_PERIOD_MS);
            abort();
        }
    }

}