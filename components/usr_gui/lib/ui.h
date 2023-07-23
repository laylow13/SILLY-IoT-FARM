// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.0
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#ifndef _SQUARELINE_PROJECT_UI_H
#define _SQUARELINE_PROJECT_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl/lvgl.h"

#include "ui_helpers.h"
#include "ui_events.h"
// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
extern lv_font_t usr_chinese_font;
extern lv_obj_t * ui_Screen1;
extern lv_obj_t * ui_Panel8;
extern lv_obj_t* ui_Panel9;
extern lv_obj_t * ui_Panel1;
extern lv_obj_t * ui_Label1;
extern lv_obj_t * temperature_data;
extern lv_obj_t * ui_Panel2;
extern lv_obj_t * ui_Label2;
extern lv_obj_t * humidity_data;
extern lv_obj_t * ui_Panel3;
extern lv_obj_t * ui_Label4;
extern lv_obj_t * pressure_data;
extern lv_obj_t * ui_Panel4;
extern lv_obj_t * ui_Label3;
extern lv_obj_t * light_intensity_data;
extern lv_obj_t * ui_Panel5;
extern lv_obj_t * ui_Label8;
extern lv_obj_t * water_Switch;
extern lv_obj_t * ui_Panel6;
extern lv_obj_t * ui_Label11;
extern lv_obj_t *light_cfg_btn;
extern lv_obj_t * light_Switch;
extern lv_obj_t* wifi_symbol;
extern lv_obj_t* wifi_label;
extern lv_obj_t * ui_Panel7;
extern lv_obj_t* auto_mode_label;
extern lv_obj_t* auto_mode_Switch;
//extern lv_obj_t* earth_humidity_panel;
extern lv_obj_t* earth_humidity_label;
extern lv_obj_t* earth_humidity_led;
extern lv_obj_t* light_sensor_data2;
extern lv_obj_t* light_sensor_label2;
extern lv_obj_t* light_sensor_data3;
extern lv_obj_t* light_sensor_label3;
extern lv_obj_t * ui____initial_actions0;

void ui_Screen2_screen_init(void);
extern  lv_obj_t* ui_Screen2;
extern  lv_obj_t* light_cfg_panel;
extern  lv_obj_t* red_slider;
extern  lv_obj_t* green_slider;
extern  lv_obj_t* blue_slider;
extern  lv_obj_t* light_cfg_label;
extern  lv_obj_t* color_panel;
extern  lv_obj_t* return_panel;
extern  lv_obj_t* return_button;
extern  lv_obj_t* button_label;


void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif