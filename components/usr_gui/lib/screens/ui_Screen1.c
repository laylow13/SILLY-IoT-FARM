// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.0
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"
#include "ui_events.h"

void ui_Screen1_screen_init(void) {
    ui_Screen1 = lv_obj_create(NULL);

    static lv_style_t label_chinese_style;
    static lv_style_t panel_content_style;

    lv_style_init(&label_chinese_style);
    lv_style_set_text_font(&label_chinese_style, &usr_chinese_font);

    lv_style_init(&panel_content_style);
    lv_style_set_width(&panel_content_style, 230);
    lv_style_set_height(&panel_content_style, 50);
    //****************状态栏***************//
    ui_Panel9 = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_Panel9, 230);
    lv_obj_set_height(ui_Panel9, 40);
    lv_obj_set_align(ui_Panel9, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_Panel9, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Panel9, lv_palette_main(LV_PALETTE_GREY), 0);

    wifi_symbol = lv_label_create(ui_Panel9);
    lv_label_set_text(wifi_symbol, LV_SYMBOL_WIFI " " LV_SYMBOL_OK);
    lv_obj_set_align(wifi_symbol, LV_ALIGN_LEFT_MID);

    wifi_label = lv_label_create(ui_Panel9);
    lv_obj_set_align(wifi_label, LV_ALIGN_RIGHT_MID);
    lv_label_set_text(wifi_label, "SMART IOT FARM");
    //****************主屏***************//
    ui_Panel8 = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_Panel8, 230);
    lv_obj_set_height(ui_Panel8, 275);
    lv_obj_set_align(ui_Panel8, LV_ALIGN_BOTTOM_MID);
    //lv_obj_clear_flag(ui_Panel8, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    //****************温度***************//
    ui_Panel1 = lv_obj_create(ui_Panel8);
    lv_obj_add_style(ui_Panel1, &panel_content_style, 0);
    lv_obj_set_align(ui_Panel1, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_Panel1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_add_flag(ui_Panel1, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_CLICK_FOCUSABLE);

    ui_Label1 = lv_label_create(ui_Panel1);
    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label1, LV_ALIGN_LEFT_MID);
    lv_obj_add_style(ui_Label1, &label_chinese_style, 0);
    lv_label_set_text(ui_Label1, "温度");
    //lv_obj_set_style_text_font(ui_Label1, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    temperature_data = lv_label_create(ui_Panel1);
    lv_obj_set_width(temperature_data, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(temperature_data, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(temperature_data, LV_ALIGN_RIGHT_MID);
    lv_obj_add_event_cb(temperature_data, common_sensor_event_cb, USR_SENSOR_UPDATE, NULL);
    //****************湿度***************//
    ui_Panel2 = lv_obj_create(ui_Panel8);
//    lv_obj_add_style(ui_Panel2, &panel_content_style, 0);
    lv_obj_set_size(ui_Panel2, 230, 100);
    lv_obj_align_to(ui_Panel2, ui_Panel1, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
    lv_obj_clear_flag(ui_Panel2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_add_flag(ui_Panel2, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_CLICK_FOCUSABLE);

    ui_Label2 = lv_label_create(ui_Panel2);
    lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label2, LV_ALIGN_TOP_LEFT);
    lv_obj_add_style(ui_Label2, &label_chinese_style, 0);
    lv_label_set_text(ui_Label2, "湿度");

    humidity_data = lv_label_create(ui_Panel2);
    lv_obj_set_width(humidity_data, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(humidity_data, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(humidity_data, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_event_cb(humidity_data, common_sensor_event_cb, USR_SENSOR_UPDATE, NULL);

    earth_humidity_label = lv_label_create(ui_Panel2);
    lv_obj_set_width(earth_humidity_label, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(earth_humidity_label, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(earth_humidity_label, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_style(earth_humidity_label, &label_chinese_style, NULL);
    lv_label_set_text(earth_humidity_label, "湿度阈值");

    earth_humidity_led = lv_led_create(ui_Panel2);
    /*lv_obj_set_width(earth_humidity_led, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(earth_humidity_led, LV_SIZE_CONTENT);    /// 1*/
    lv_obj_set_align(earth_humidity_led, LV_ALIGN_BOTTOM_RIGHT);
    lv_led_off(earth_humidity_led);
    //****************土壤湿度***************//

    //****************压强***************//
    ui_Panel3 = lv_obj_create(ui_Panel8);
    lv_obj_add_style(ui_Panel3, &panel_content_style, 0);
    lv_obj_align_to(ui_Panel3, ui_Panel2, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
    lv_obj_clear_flag(ui_Panel3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_add_flag(ui_Panel3, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_CLICK_FOCUSABLE);

    ui_Label4 = lv_label_create(ui_Panel3);
    lv_obj_set_width(ui_Label4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label4, LV_ALIGN_LEFT_MID);
    lv_obj_add_style(ui_Label4, &label_chinese_style, 0);
    lv_label_set_text(ui_Label4, "压强");

    pressure_data = lv_label_create(ui_Panel3);
    lv_obj_set_width(pressure_data, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(pressure_data, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(pressure_data, LV_ALIGN_RIGHT_MID);
    lv_obj_add_event_cb(pressure_data, common_sensor_event_cb, USR_SENSOR_UPDATE, NULL);
    //****************光强***************//
    ui_Panel4 = lv_obj_create(ui_Panel8);
    lv_obj_set_size(ui_Panel4, 230, 150);
//    lv_obj_add_style(ui_Panel4, &panel_content_style, 0);
    lv_obj_align_to(ui_Panel4, ui_Panel3, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
    lv_obj_clear_flag(ui_Panel4, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_add_flag(ui_Panel4, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_CLICK_FOCUSABLE);

    ui_Label3 = lv_label_create(ui_Panel4);
    lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label3, LV_ALIGN_TOP_LEFT);
    lv_obj_add_style(ui_Label3, &label_chinese_style, 0);
    lv_label_set_text(ui_Label3, "光强");

    light_intensity_data = lv_label_create(ui_Panel4);
    lv_obj_set_width(light_intensity_data, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(light_intensity_data, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(light_intensity_data, LV_ALIGN_TOP_RIGHT);
    static uint8_t light_data_id_1 = 1;
    lv_obj_add_event_cb(light_intensity_data, light_sensor_event_cb, USR_SENSOR_UPDATE, &light_data_id_1);

    light_sensor_label2 = lv_label_create(ui_Panel4);
    lv_obj_set_width(light_sensor_label2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(light_sensor_label2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(light_sensor_label2, LV_ALIGN_LEFT_MID);
    lv_obj_add_style(light_sensor_label2, &label_chinese_style, NULL);
    lv_label_set_text(light_sensor_label2, "波长");

    light_sensor_data2 = lv_label_create(ui_Panel4);
    lv_obj_set_width(light_sensor_data2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(light_sensor_data2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(light_sensor_data2, LV_ALIGN_RIGHT_MID);
    static uint8_t light_data_id_2 = 2;
    lv_obj_add_event_cb(light_sensor_data2, light_sensor_event_cb, USR_SENSOR_UPDATE, &light_data_id_2);

    light_sensor_label3 = lv_label_create(ui_Panel4);
    lv_obj_set_width(light_sensor_label3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(light_sensor_label3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(light_sensor_label3, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_style(light_sensor_label3, &label_chinese_style, NULL);
    lv_label_set_text(light_sensor_label3, "色温");

    light_sensor_data3 = lv_label_create(ui_Panel4);
    lv_obj_set_width(light_sensor_data3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(light_sensor_data3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(light_sensor_data3, LV_ALIGN_BOTTOM_RIGHT);
    static uint8_t light_data_id_3 = 3;
    lv_obj_add_event_cb(light_sensor_data3, light_sensor_event_cb, USR_SENSOR_UPDATE, &light_data_id_3);

    //****************浇水***************//
    ui_Panel5 = lv_obj_create(ui_Panel8);
    lv_obj_add_style(ui_Panel5, &panel_content_style, 0);
    lv_obj_align_to(ui_Panel5, ui_Panel4, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
    lv_obj_clear_flag(ui_Panel5, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label8 = lv_label_create(ui_Panel5);
    lv_obj_set_width(ui_Label8, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label8, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label8, LV_ALIGN_LEFT_MID);
    lv_obj_add_style(ui_Label8, &label_chinese_style, 0);
    lv_label_set_text(ui_Label8, "浇水");

    water_Switch = lv_switch_create(ui_Panel5);
    lv_obj_set_width(water_Switch, 50);
    lv_obj_set_height(water_Switch, 25);
    lv_obj_set_align(water_Switch, LV_ALIGN_RIGHT_MID);
    static uint8_t water_switch_id = 0;
    lv_obj_add_event_cb(water_Switch, switch_event_cb, LV_EVENT_CLICKED, &water_switch_id);
    //****************灯光***************//
    ui_Panel6 = lv_obj_create(ui_Panel8);
    lv_obj_add_style(ui_Panel6, &panel_content_style, 0);
    lv_obj_align_to(ui_Panel6, ui_Panel5, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
    lv_obj_clear_flag(ui_Panel6, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label11 = lv_label_create(ui_Panel6);
    lv_obj_set_width(ui_Label11, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label11, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label11, LV_ALIGN_LEFT_MID);
    lv_obj_add_style(ui_Label11, &label_chinese_style, 0);
    lv_label_set_text(ui_Label11, "灯光");

    light_cfg_btn = lv_btn_create(ui_Panel6);
    lv_obj_set_align(light_cfg_btn, LV_ALIGN_CENTER);
    lv_obj_set_size(light_cfg_btn, 50, 25);
    lv_obj_t *light_btn_label = lv_label_create(light_cfg_btn);
    lv_obj_add_style(light_btn_label, &label_chinese_style, 0);
    lv_label_set_text(light_btn_label, "配置");
    lv_obj_center(light_btn_label);
    lv_obj_set_style_bg_color(light_cfg_btn, lv_palette_main(LV_PALETTE_GREY), 0);
    lv_obj_add_event_cb(light_cfg_btn, light_cfg_entrence, LV_EVENT_CLICKED, NULL);

    light_Switch = lv_switch_create(ui_Panel6);
    lv_obj_set_width(light_Switch, 50);
    lv_obj_set_height(light_Switch, 25);
    lv_obj_set_align(light_Switch, LV_ALIGN_RIGHT_MID);
    static uint8_t light_switch_id = 1;
    lv_obj_add_event_cb(light_Switch, switch_event_cb, LV_EVENT_CLICKED, &light_switch_id);
    ///
    ui_Panel7 = lv_obj_create(ui_Panel8);
    lv_obj_add_style(ui_Panel7, &panel_content_style, 0);
    lv_obj_align_to(ui_Panel7, ui_Panel6, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
    lv_obj_clear_flag(ui_Panel7, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    auto_mode_label = lv_label_create(ui_Panel7);
    lv_obj_set_width(auto_mode_label, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(auto_mode_label, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(auto_mode_label, LV_ALIGN_LEFT_MID);
    lv_obj_add_style(auto_mode_label, &label_chinese_style, 0);
    lv_label_set_text(auto_mode_label, "专家模式");

    auto_mode_Switch = lv_switch_create(ui_Panel7);
    lv_obj_set_width(auto_mode_Switch, 50);
    lv_obj_set_height(auto_mode_Switch, 25);
    lv_obj_set_align(auto_mode_Switch, LV_ALIGN_RIGHT_MID);
}
