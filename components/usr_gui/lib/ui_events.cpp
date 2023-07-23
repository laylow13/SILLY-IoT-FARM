//
// Created by Lay on 7/13/2023.
//
#include "ui_events.h"
#include "usr_motor.h"
#include "usr_light.h"
#include "esp_log.h"
#include "ui.h"

extern "C" {
inline void slider_check_max(lv_obj_t *x) { if (lv_slider_get_value(x) == 100) lv_slider_set_value(x, 0, LV_ANIM_ON); }
uint32_t USR_SENSOR_UPDATE = lv_event_register_id();
usr::color_t light_color{0xff, 0xff, 0xff, 0};

void switch_event_cb(lv_event_t *event) {
    lv_obj_t *tar = lv_event_get_target(event);
    bool switch_on = lv_obj_has_state(tar, LV_STATE_CHECKED);
    uint8_t *switch_id = (uint8_t *) lv_event_get_user_data(event);
    if (*switch_id == 0) {
        //water switch
        ESP_LOGI("LVGL", "motor switch event triggered");
        int motor_level = int(switch_on);
        xQueueSend(usr::motor_queue, &motor_level, pdMS_TO_TICKS(5));
    } else if (*switch_id == 1) {
        //light switch
        usr::color_t cmd{};
        if (switch_on) {
            cmd = light_color;
        } else {
            cmd = {0, 0, 0, 0};
        }
        ESP_LOGI("LVGL", "light switch event triggered");
        xQueueSend(usr::light_queue, &cmd, pdMS_TO_TICKS(5));
    }
}

void common_sensor_event_cb(lv_event_t *event) {
    auto event_code = lv_event_get_code(event);
    if (event_code == USR_SENSOR_UPDATE) {
        auto tar = lv_event_get_target(event);
        auto sensor_data = (float *) lv_event_get_param(event);
        lv_label_set_text_fmt(tar, "%.2f", *sensor_data);
        ESP_LOGI("LVGL", "common sensor data update:%f", *sensor_data);
    }
}

void light_sensor_event_cb(lv_event_t *event) {
    auto event_code = lv_event_get_code(event);
    if (event_code == USR_SENSOR_UPDATE) {
        auto tar = lv_event_get_target(event);
        auto *data_id = (uint8_t *) lv_event_get_user_data(event);
        if (*data_id == 1) {
            auto light_intensity = (float *) lv_event_get_param(event);
            lv_label_set_text_fmt(tar, "%.2flux", *light_intensity);
        } else if (*data_id == 2) {
            auto wave_length = (float *) lv_event_get_param(event);
            lv_label_set_text_fmt(tar, "%.2f", *wave_length);
        } else if (*data_id == 3) {
            auto cct = (float *) lv_event_get_param(event);
            lv_label_set_text_fmt(tar, "%.2f", *cct);
        }
        ESP_LOGI("LVGL", "light sensor data update");
    }
}

void light_cfg_entrence(lv_event_t *event) {
    lv_disp_load_scr(ui_Screen2);
}
void light_cfg_out(lv_event_t *event) {
    lv_disp_load_scr(ui_Screen1);
}
void light_color_update(lv_event_t *event) {
    slider_check_max(red_slider);
    slider_check_max(green_slider);
    slider_check_max(blue_slider);
    auto red = lv_slider_get_value(red_slider);
    auto green = lv_slider_get_value(green_slider);
    auto blue = lv_slider_get_value(blue_slider);
    lv_obj_set_style_bg_color(color_panel, lv_color_make(red * 255 / 100, green * 255 / 100, blue * 255 / 100), 0);
    light_color.red = red * 255 / 100;
    light_color.green = green * 255 / 100;
    light_color.blue = blue * 255 / 100;
}
}