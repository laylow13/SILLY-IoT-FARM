idf_component_register(SRCS usr_sensors.cpp
        INCLUDE_DIRS .
        REQUIRES "sensor_hub" "bme280" usr_gui usr_cloud)