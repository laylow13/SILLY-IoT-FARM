//
// Created by Lay on 7/20/2023.
//
#include "../ui.h"
#include "ui_events.h"



void ui_Screen2_screen_init(void)
{
    ui_Screen2 = lv_obj_create(NULL);

    static lv_style_t label_chinese_style;
    static lv_style_t color_bar_style;

    lv_style_init(&label_chinese_style);
    lv_style_set_text_font(&label_chinese_style, &usr_chinese_font);

    lv_style_init(&color_bar_style);
    lv_style_set_width(&color_bar_style, 180);

    light_cfg_panel = lv_obj_create(ui_Screen2);
    lv_obj_set_width(light_cfg_panel, 230);
    lv_obj_set_height(light_cfg_panel, LV_SIZE_CONTENT);
    lv_obj_set_align(light_cfg_panel, LV_ALIGN_TOP_MID);
    static lv_coord_t col_dsc[] = {15, 195, LV_GRID_TEMPLATE_LAST };
    static lv_coord_t row_dsc[] = { 30, 30, 30,30,30, LV_GRID_TEMPLATE_LAST };
    lv_obj_set_style_grid_column_dsc_array(light_cfg_panel, col_dsc, 0);
    lv_obj_set_style_grid_row_dsc_array(light_cfg_panel, row_dsc, 0);
    lv_obj_set_layout(light_cfg_panel, LV_LAYOUT_GRID);
    lv_obj_clear_flag(light_cfg_panel, LV_OBJ_FLAG_SCROLLABLE);

    light_cfg_label =lv_label_create(light_cfg_panel);
    lv_obj_add_style(light_cfg_label, &label_chinese_style, 0);
    lv_label_set_text(light_cfg_label,"灯光配置");
    lv_obj_set_grid_cell(light_cfg_label, LV_GRID_ALIGN_CENTER, 0, 2,
                         LV_GRID_ALIGN_CENTER, 0, 1);
    //****************red***************//
    lv_obj_t*red_label= lv_label_create(light_cfg_panel);
    lv_obj_add_style(red_label, &label_chinese_style, 0);
    lv_label_set_text(red_label,"红");
    lv_obj_set_grid_cell(red_label, LV_GRID_ALIGN_CENTER, 0, 1,
                         LV_GRID_ALIGN_CENTER, 1, 1);
    red_slider=lv_slider_create(light_cfg_panel);
    lv_obj_add_style(red_slider, &color_bar_style, 0);
    lv_obj_set_grid_cell(red_slider, LV_GRID_ALIGN_CENTER, 1, 1,
                         LV_GRID_ALIGN_CENTER, 1, 1);
    lv_obj_set_style_bg_color(red_slider, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN);
    lv_obj_set_style_bg_color(red_slider, lv_palette_main(LV_PALETTE_RED), LV_PART_INDICATOR);
    lv_slider_set_value(red_slider, 50, LV_ANIM_ON);
    lv_obj_add_event_cb(red_slider, light_color_update, LV_EVENT_VALUE_CHANGED, NULL);
    //****************green***************//
    lv_obj_t* green_label = lv_label_create(light_cfg_panel);
    lv_obj_add_style(green_label, &label_chinese_style, 0);
    lv_label_set_text(green_label, "绿");
    lv_obj_set_grid_cell(green_label, LV_GRID_ALIGN_CENTER, 0, 1,
                         LV_GRID_ALIGN_CENTER, 2, 1);
    green_slider = lv_slider_create(light_cfg_panel);
    lv_obj_add_style(green_slider, &color_bar_style, 0);
    lv_obj_set_grid_cell(green_slider, LV_GRID_ALIGN_CENTER, 1, 1,
                         LV_GRID_ALIGN_CENTER, 2, 1);
    lv_obj_set_style_bg_color(green_slider, lv_palette_main(LV_PALETTE_GREEN), LV_PART_MAIN);
    lv_obj_set_style_bg_color(green_slider, lv_palette_main(LV_PALETTE_GREEN), LV_PART_INDICATOR);
    lv_slider_set_value(green_slider, 50, LV_ANIM_ON);
    lv_obj_add_event_cb(green_slider, light_color_update, LV_EVENT_VALUE_CHANGED, NULL);
    //****************blue***************//
    lv_obj_t* blue_label = lv_label_create(light_cfg_panel);
    lv_obj_add_style(blue_label, &label_chinese_style, 0);
    lv_label_set_text(blue_label, "蓝");
    lv_obj_set_grid_cell(blue_label, LV_GRID_ALIGN_CENTER, 0, 1,
                         LV_GRID_ALIGN_CENTER, 3, 1);
    blue_slider = lv_slider_create(light_cfg_panel);
    lv_obj_add_style(blue_slider, &color_bar_style, 0);
    lv_obj_set_grid_cell(blue_slider, LV_GRID_ALIGN_CENTER, 1, 1,
                         LV_GRID_ALIGN_CENTER, 3, 1);
    lv_obj_set_style_bg_color(blue_slider, lv_palette_main(LV_PALETTE_BLUE), LV_PART_MAIN);
    lv_obj_set_style_bg_color(blue_slider, lv_palette_main(LV_PALETTE_BLUE), LV_PART_INDICATOR);
    lv_slider_set_value(blue_slider, 50, LV_ANIM_ON);
    lv_obj_add_event_cb(blue_slider, light_color_update, LV_EVENT_VALUE_CHANGED, NULL);
    //****************color_panel***************//
    color_panel = lv_obj_create(light_cfg_panel);
    lv_obj_set_size(color_panel, 100,30);
    lv_obj_set_grid_cell(color_panel, LV_GRID_ALIGN_CENTER, 0, 2,
                         LV_GRID_ALIGN_CENTER, 4, 1);
    lv_obj_set_style_bg_color(color_panel, lv_color_make(255/2,255/2,255/2),0);

    return_button= lv_btn_create(ui_Screen2);
    lv_obj_set_width(return_button, 230);
    lv_obj_align_to(return_button, light_cfg_panel, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
    button_label= lv_label_create(return_button);
    lv_obj_center(button_label);
    lv_obj_add_style(button_label, &label_chinese_style, 0);
    lv_label_set_text(button_label,"返回");
    lv_obj_add_event_cb(return_button,light_cfg_out,LV_EVENT_CLICKED,NULL);

}
