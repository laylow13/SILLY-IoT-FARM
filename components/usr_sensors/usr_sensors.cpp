//
// Created by Lay on 5/4/2023.
//
#include "esp_log.h"
#include "usr_sensors.h"
#include "bme280.h"
#include "ui.h"
#include "esp_lvgl_port.h"
#include "usr_cloud_service.h"
#include <cmath>

namespace usr {
    static sensor_humiture_handle_t humiture_handle;
    static bme280_handle_t pressure_handle;
    static sensor_light_handle_t light_handle;
    xQueueHandle sensor_data_queue;
    using namespace std;

    static float calculate_wavelength(rgbw_t rgbw) {
        auto red = rgbw.r;
        auto green = rgbw.g;
        auto blue = rgbw.b;
        auto wavelength = 0;
        if (red == green and green == blue)
            wavelength = -1;
        else if (red >= green and red >= blue)
            wavelength = 700 - ((green - blue) / (red - fmin(green, blue))) * 400;
        else if (green >= red and green >= blue)
            wavelength = 500 + ((red - blue) / (green - fmin(red, blue))) * 200;
        else
            wavelength = 400 + ((blue - green) / (blue - fmin(red, green))) * 100;
        return wavelength;
    }

    static esp_err_t sensors_init() {
        i2c_port_t i2c_port = 0;
        i2c_config_t conf{
                I2C_MODE_MASTER, 18, 17,
                GPIO_PULLUP_DISABLE, GPIO_PULLUP_DISABLE, {{100000}}, 0};
        auto i2c_bus = i2c_bus_create(i2c_port, &conf);
        esp_err_t ret;
#if (CONFIG_USR_SENSOR_USE_SHT3x)
        humiture_handle = humiture_create(i2c_bus, SHT3X_ID);
        ret = humiture_test(humiture_handle);
        if (ret == ESP_FAIL) {
            ESP_LOGE("sensor", "humiture sensor init error!");
            return ESP_FAIL;
        }
#endif
#if (CONFIG_USR_SENSOR_USE_BME280)
        pressure_handle = bme280_create(i2c_bus, BME280_I2C_ADDRESS_DEFAULT);
        ret = bme280_default_init(pressure_handle);
        if (ret == ESP_FAIL) {
            ESP_LOGE("sensor", "pressure sensor init error!");
            return ESP_FAIL;
        }
#endif
#if (CONFIG_USR_SENSOR_USE_VMEL6040)
        light_handle = light_sensor_create(i2c_bus, VEML6040_ID);
        ret = light_sensor_test(light_handle);
        if (ret == ESP_FAIL) {
            ESP_LOGE("sensor", "light sensor init error!");
            return ESP_FAIL;
        }
#endif
        //earth humidity
        gpio_config_t config{1ULL << 41, GPIO_MODE_INPUT,
                             GPIO_PULLUP_DISABLE, GPIO_PULLDOWN_DISABLE,
                             GPIO_INTR_DISABLE};
        gpio_config(&config);

        return ESP_OK;
    }

    static void sensors_task(void *pvParameters) {
        TickType_t lastwaketime = xTaskGetTickCount();
        sensor_data_queue = xQueueCreate(10, sizeof(sensor_data_t));
        float humidity, temperature, pressure, wave_length, ambient_light_Lux, cct = 0;
        rgbw_t light_rgbw{};
        light_data_t light_sensor_data{};
        sensor_data_t sensor_data{};
        while (1) {
            esp_err_t ret;
#if CONFIG_USR_SENSOR_USE_SHT3x
            ret = humiture_acquire_humidity(humiture_handle, &humidity);
            if (ret == ESP_FAIL) {
                ESP_LOGW("sensor", "humidity data access error!");
            } else {
                lvgl_port_lock(0);
                lv_event_send(humidity_data, (lv_event_code_t) (USR_SENSOR_UPDATE), &humidity);
                lvgl_port_unlock();
                ESP_ERROR_CHECK(esp_rmaker_param_update_and_report(humidity_value, esp_rmaker_float(humidity)));
            }
#else
            humidity = .0;
#endif
#if (CONFIG_USR_SENSOR_USE_SHT3x)
            ret = humiture_acquire_temperature(humiture_handle, &temperature);
            if (ret == ESP_FAIL) {
                ESP_LOGW("sensor", "temperature data access error!");
            } else {
                lvgl_port_lock(0);
                lv_event_send(temperature_data, (lv_event_code_t) (USR_SENSOR_UPDATE), &temperature);
                lvgl_port_unlock();
                ESP_ERROR_CHECK(esp_rmaker_param_update_and_report(temperature_value, esp_rmaker_float(temperature)));
            }
#else
            temperature = .0;
#endif
#if CONFIG_USR_SENSOR_USE_BME280
            ret = bme280_read_pressure(pressure_handle, &pressure);
            if (ret == ESP_FAIL) {
                ESP_LOGW("sensor", "pressure data access error!");
            } else {
                lvgl_port_lock(0);
                lv_event_send(pressure_data, (lv_event_code_t) (USR_SENSOR_UPDATE), &pressure);
                lvgl_port_unlock();
                ESP_ERROR_CHECK(esp_rmaker_param_update_and_report(pressure_value, esp_rmaker_float(pressure)));
            }
#else
            pressure = .0;
#endif
#if CONFIG_USR_SENSOR_USE_VMEL6040
            ret = light_sensor_acquire_rgbw(light_handle, &light_rgbw);
            wave_length = calculate_wavelength(light_rgbw);
            ambient_light_Lux = light_rgbw.g * .06292f;
            auto ccti = ((float) light_rgbw.r - (float) light_rgbw.b) / (float) light_rgbw.g;
            cct = 4278.6 * pow(ccti, -1.2455);
            light_sensor_data = {wave_length, ambient_light_Lux, cct, light_rgbw};
            if (ret == ESP_FAIL) {
                ESP_LOGW("sensor", "light data access error!");
            } else {
                lvgl_port_lock(0);
                lv_event_send(light_intensity_data, (lv_event_code_t) (USR_SENSOR_UPDATE), &ambient_light_Lux);
                lv_event_send(light_sensor_data2, (lv_event_code_t) (USR_SENSOR_UPDATE), &wave_length);
                lv_event_send(light_sensor_data3, (lv_event_code_t) (USR_SENSOR_UPDATE), &cct);
                lvgl_port_unlock();
                ESP_ERROR_CHECK(
                        esp_rmaker_param_update_and_report(light_lux_value, esp_rmaker_float(ambient_light_Lux)));
                ESP_ERROR_CHECK(esp_rmaker_param_update_and_report(light_cct_value, esp_rmaker_float(cct)));
                ESP_ERROR_CHECK(
                        esp_rmaker_param_update_and_report(light_wavelength_value, esp_rmaker_float(wave_length)));
            }
#else
            light_intensity = .0;
            light_rgbw = {};
            light_uv = {};

#endif
            //earth humidity
            int earth_humidity_threshold = gpio_get_level(GPIO_NUM_41);
            lvgl_port_lock(0);
            if (earth_humidity_threshold)
                lv_led_on(earth_humidity_led);
            else
                lv_led_off(earth_humidity_led);
            lvgl_port_unlock();

            sensor_data = {humidity, temperature, pressure, light_sensor_data};
            ESP_LOGI("usr sensors", "humidity:%f,temperature:%f,pressure:%f", humidity, temperature, pressure);
            ESP_LOGI("usr sensors", "light r:%f,g:%f,b:%f,w:%f", light_rgbw.r, light_rgbw.g, light_rgbw.b,
                     light_rgbw.w);
            xQueueSend(sensor_data_queue, &sensor_data, 10 / portTICK_PERIOD_MS);
            vTaskDelayUntil(&lastwaketime, 10000 / portTICK_PERIOD_MS);
        }
    }

    esp_err_t sensors_task_create() {
        esp_err_t ret = sensors_init();
        if (ret == ESP_FAIL) {
            ESP_LOGE("sensor", "sensor task aborted");
            return ESP_FAIL;
        }
        xTaskCreate(sensors_task, "sensors", 4096, nullptr, 2, nullptr);
        return ESP_OK;
    }

    esp_err_t sensors_gui_test() {
        static float test_value = 1.34;
        lvgl_port_lock(0);
        lv_event_send(humidity_data, (lv_event_code_t) (USR_SENSOR_UPDATE), &test_value);
        lv_event_send(temperature_data, (lv_event_code_t) (USR_SENSOR_UPDATE), &test_value);
        lv_event_send(pressure_data, (lv_event_code_t) (USR_SENSOR_UPDATE), &test_value);
        lv_event_send(light_intensity_data, (lv_event_code_t) (USR_SENSOR_UPDATE), &test_value);
        lvgl_port_unlock();
        return ESP_OK;
    }

}