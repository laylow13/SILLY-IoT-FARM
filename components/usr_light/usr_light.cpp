//
// Created by Lay on 5/4/2023.
//


#include "usr_light.h"
#include "esp_log.h"
#include "esp_check.h"


namespace usr {
    xQueueHandle light_queue = xQueueCreate(1, sizeof(color_t));

    static void light_task(void *pvParameters) {
        color_t color{0, 0xff, 0, 0};
        led_state new_state{};
        uint32_t color_value;
        while (1) {
            color_value = color.green << 16 | color.red << 8 | color.blue;
            for (auto &&i: new_state.leds) {
                i = color_value;
            }
            ESP_ERROR_CHECK(ws2812_write_leds(new_state));
            xQueueReceive(light_queue, &color, portMAX_DELAY);
            ESP_LOGI("light", "light command received,R:%d,G:%d,B:%d", color.red, color.green, color.blue);
        }
    }

    esp_err_t light_task_create() {
        ESP_RETURN_ON_ERROR(ws2812_control_init(), "light", "led init error,task aborted");
        light_queue = xQueueCreate(1, sizeof(color_t));
        xTaskCreate(light_task, "light task", 2048, nullptr, 2, nullptr);
        return ESP_OK;
    }

}