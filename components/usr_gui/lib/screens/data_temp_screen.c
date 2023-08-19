//
// Created by Lay on 8/17/2023.
//
#include "lvgl.h"
#include "ui_events.h"

lv_obj_t *chart;
lv_obj_t *data_temp_screen;
lv_chart_series_t *ser;
lv_chart_series_t *up_ser;
lv_chart_series_t *dn_ser;
lv_obj_t *up_num;
lv_obj_t *dn_num;
lv_obj_t *up_btn;
lv_obj_t *temp_chart;
lv_obj_t *dn_btn;
lv_obj_t *rtn_btn;
lv_group_t *temp_screen_group;
lv_obj_t *data_input_screen;
uint8_t event_id;
lv_obj_t *kb;
lv_group_t *input_screen_group;

void data_temp_screen_init() {
    data_temp_screen = lv_obj_create(NULL);

    up_btn = lv_btn_create(data_temp_screen);
    lv_obj_set_size(up_btn, 230, 30);
    lv_obj_align(up_btn, LV_ALIGN_TOP_MID, 0, 5);
    lv_obj_t *up_label = lv_label_create(up_btn);
    lv_label_set_text(up_label, "up limit");
    up_num = lv_label_create(up_btn);
    lv_obj_align(up_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_align(up_num, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_label_set_text(up_num,"0.0");
    static uint8_t up_id = 0;
    lv_obj_add_event_cb(up_btn, data_input_event, LV_EVENT_CLICKED, &up_id);

    dn_btn = lv_btn_create(data_temp_screen);
    lv_obj_set_size(dn_btn, 230, 30);
    lv_obj_align_to(dn_btn, up_btn, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
    lv_obj_t *dn_label = lv_label_create(dn_btn);
    lv_label_set_text(dn_label, "down limit");
    dn_num = lv_label_create(dn_btn);
    lv_obj_align(dn_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_align(dn_num, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_label_set_text(dn_num,"0.0");
    static uint8_t dn_id = 1;
    lv_obj_add_event_cb(dn_btn, data_input_event, LV_EVENT_CLICKED, &dn_id);

    temp_chart = lv_chart_create(data_temp_screen);
    lv_obj_set_size(temp_chart, 180, 180);
    lv_chart_set_range(temp_chart, LV_CHART_AXIS_PRIMARY_Y, 0, 40);
    lv_obj_align_to(temp_chart, dn_btn, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
    lv_chart_set_axis_tick(temp_chart, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 5, 5, true, 20);
    lv_chart_set_axis_tick(temp_chart, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 12, 1, true, 30);
    lv_obj_refresh_ext_draw_size(temp_chart);
    ser = lv_chart_add_series(temp_chart, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_PRIMARY_Y);
    up_ser = lv_chart_add_series(temp_chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
    dn_ser = lv_chart_add_series(temp_chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);

    rtn_btn = lv_btn_create(data_temp_screen);
    lv_obj_align(rtn_btn, LV_ALIGN_BOTTOM_MID, 0, -20);
    lv_obj_set_size(rtn_btn, 230, 30);
    lv_obj_t *rtn_label = lv_label_create(rtn_btn);
    lv_label_set_text(rtn_label, "返回");
    lv_obj_center(rtn_label);
    lv_obj_add_event_cb(rtn_btn, light_cfg_out, LV_EVENT_CLICKED, NULL);

    temp_screen_group =lv_group_create();
    lv_group_add_obj(temp_screen_group,up_btn);
    lv_group_add_obj(temp_screen_group,dn_btn);
    lv_group_add_obj(temp_screen_group,rtn_btn);

}

lv_obj_t *kb;
float kb_val;
float dn_val;
float up_val;


void data_input_screen_init(void) {
    /*Create the text area*/
    data_input_screen = lv_obj_create(NULL);

    lv_obj_t *ta = lv_textarea_create(data_input_screen);
    lv_obj_set_size(ta, LV_HOR_RES, 50);
    lv_obj_add_event_cb(ta, ta_event_cb, LV_EVENT_ALL, NULL);
    lv_textarea_set_accepted_chars(ta, "0123456789.");
    lv_textarea_set_max_length(ta, 5);
    lv_textarea_set_one_line(ta, true);
    lv_textarea_set_text(ta, "");
    lv_obj_align(ta, LV_ALIGN_TOP_MID, 0, 5);

    /*Create a keyboard*/
    kb = lv_keyboard_create(data_input_screen);
    lv_obj_set_size(kb, LV_HOR_RES, LV_VER_RES / 2);
    lv_obj_align(kb, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_keyboard_set_mode(kb, LV_KEYBOARD_MODE_NUMBER);
    lv_keyboard_set_textarea(kb, ta);

    input_screen_group =lv_group_create();
    lv_group_add_obj(input_screen_group,kb);

}

