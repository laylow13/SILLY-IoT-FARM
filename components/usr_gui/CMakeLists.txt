idf_component_register(SRCS
        usr_gui.cpp
        lib/screens/ui_Screen1.c
        lib/screens/ui_Screen2.c
        lib/fonts/usr_chinese_font.c
        lib/ui.c
        lib/ui_events.cpp
        lib/ui_helpers.c
        INCLUDE_DIRS . lib
        REQUIRES button esp_lvgl_port lvgl usr_motor usr_light)