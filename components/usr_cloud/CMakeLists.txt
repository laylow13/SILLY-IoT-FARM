idf_component_register(SRCS usr_cloud_service.cpp
        INCLUDE_DIRS .
        REQUIRES esp_rainmaker app_insights app_wifi nvs_flash usr_gui usr_light usr_motor)