//
// Created by Lay on 5/4/2023.
//
#include "ui.h"
#include "usr_gui.h"
#include "esp_check.h"
#include "lvgl.h"
#include "esp_lvgl_port.h"
#include "driver/spi_master.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "esp_heap_caps.h"
#include "driver/gpio.h"
#include "iot_button.h"
#include "examples/lv_examples.h"

#define LCD_HOST SPI2_HOST
#define LCD_PIXEL_CLOCK_HZ (10 * 1000 * 1000)
#define PIN_NUM_DATA0 11 /*!< for 1-line SPI, this also refered as MOSI */
#define PIN_NUM_PCLK 12
#define PIN_NUM_CS 10
#define PIN_NUM_DC 46
#define PIN_NUM_RST 3

#define LCD_H_RES 240
#define LCD_V_RES 320
#define LCD_CMD_BITS 8
#define LCD_PARAM_BITS 8
#define BUFFER_SZ (LCD_V_RES * 30)

namespace usr {
    static lv_disp_t *disp;
    lv_indev_t *indev_handle;
    lv_group_t *input_group;

    static esp_err_t disp_init(esp_lcd_panel_io_handle_t *_io_handle, esp_lcd_panel_handle_t *_panel_handle) {
        spi_bus_config_t buscfg = {
                .mosi_io_num = PIN_NUM_DATA0,
                .miso_io_num=-1,
                .sclk_io_num = PIN_NUM_PCLK,
                .quadwp_io_num=-1,
                .quadhd_io_num = -1,
                .data4_io_num=-1,
                .data5_io_num=-1,
                .data6_io_num=-1,
                .data7_io_num=-1,
                .max_transfer_sz = BUFFER_SZ * sizeof(uint16_t) + 8
        };

        // Initialize the SPI bus
        ESP_RETURN_ON_ERROR(spi_bus_initialize(LCD_HOST, &buscfg, SPI_DMA_CH_AUTO), "spi_host", "spi init error");
        esp_lcd_panel_io_spi_config_t io_config = {
                .cs_gpio_num=PIN_NUM_CS,
                .dc_gpio_num=PIN_NUM_DC,
                .spi_mode=0,
                .pclk_hz= LCD_PIXEL_CLOCK_HZ,
                .trans_queue_depth= 10,
                .on_color_trans_done= nullptr,
                .user_ctx=nullptr,
                .lcd_cmd_bits= LCD_CMD_BITS,
                .lcd_param_bits= LCD_PARAM_BITS,
        };
        // Attach the LCD to the SPI bus
        ESP_RETURN_ON_ERROR(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t) LCD_HOST, &io_config, _io_handle),
                            "spi_lcd", "panel spi init error");

        esp_lcd_panel_dev_config_t panel_config = {
                .reset_gpio_num = PIN_NUM_RST,
                .color_space = ESP_LCD_COLOR_SPACE_RGB,
                .bits_per_pixel = 16,
        };
        // Initialize the LCD configuration
        ESP_ERROR_CHECK(esp_lcd_new_panel_st7789(*_io_handle, &panel_config, _panel_handle));
        // Reset the display
        ESP_ERROR_CHECK(esp_lcd_panel_reset(*_panel_handle));
        // Initialize LCD panel
        ESP_ERROR_CHECK(esp_lcd_panel_init(*_panel_handle));
        ESP_ERROR_CHECK(esp_lcd_panel_mirror(*_panel_handle, true, true));
        ESP_ERROR_CHECK(esp_lcd_panel_invert_color(*_panel_handle, true));
        return ESP_OK;
    }

    static esp_err_t lv_add_disp() {
        esp_lcd_panel_io_handle_t io_handle = nullptr;
        esp_lcd_panel_handle_t panel_handle = nullptr;
        ESP_RETURN_ON_ERROR(disp_init(&io_handle, &panel_handle), "display", "disp init error");
        /* Add LCD screen */
        const lvgl_port_display_cfg_t disp_cfg = {
                .io_handle = io_handle,
                .panel_handle = panel_handle,
                .buffer_size = BUFFER_SZ,
                .double_buffer = true,
                .hres = LCD_H_RES,
                .vres = LCD_V_RES,
                .monochrome = false,
                /* Rotation values must be same as used in esp_lcd for initial settings of the screen */
                .rotation = {
                        .swap_xy = false,
                        .mirror_x = true,
                        .mirror_y = true,
                },
                .flags = {
                        .buff_dma = true,
                }};
        disp = lvgl_port_add_disp(&disp_cfg);
        return ESP_OK;
    }

    static void lv_add_indev() {
        const button_config_t button_config[] = {
                {
                        .type = BUTTON_TYPE_GPIO,
                        .long_press_time=0,
                        .short_press_time=0,
                        .gpio_button_config={
                                .gpio_num = 21,
                                .active_level = 0
                        }
                },
                {
                        .type = BUTTON_TYPE_GPIO,
                        .long_press_time=0,
                        .short_press_time=0,
                        .gpio_button_config={
                                .gpio_num = 47,
                                .active_level = 0
                        },
                },
        };
        const lvgl_port_nav_btns_cfg_t btns = {
                .disp = disp,
                .button_prev = nullptr,
                .button_next = &button_config[0],
                .button_enter = &button_config[1],
        };
        indev_handle = lvgl_port_add_navigation_buttons(&btns);
    }

    static void gui_create() {
        /* Wait for the other task done the screen operation */
        lvgl_port_lock(0);
        input_group= lv_group_create();
        lv_indev_set_group(indev_handle, input_group);
        ui_init();
        lv_group_add_obj(input_group,ui_Panel1);
        lv_group_add_obj(input_group,ui_Panel2);
        lv_group_add_obj(input_group,ui_Panel3);
        lv_group_add_obj(input_group,ui_Panel4);
        lv_group_add_obj(input_group, water_Switch);
        lv_group_add_obj(input_group, light_Switch);
        lv_group_add_obj(input_group, light_cfg_btn);
//        lv_group_add_obj(input_group, auto_mode_Switch);
        lvgl_port_unlock();
    }

    esp_err_t gui_task_create() {
        const lvgl_port_cfg_t lvgl_cfg = ESP_LVGL_PORT_INIT_CONFIG();
        ESP_RETURN_ON_ERROR(lvgl_port_init(&lvgl_cfg), "lvgl", "lvgl init error");
        lv_add_disp();
        lv_add_indev();
        gui_create();
        return ESP_OK;
    }
}