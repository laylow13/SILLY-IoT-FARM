#common requires
set(requires bus)
#imu sensor requires
#list(APPEND requires mpu6050 lis2dh12)
#humiture sensor requires
list(APPEND requires sht3x)
#light sensor requires
list(APPEND requires veml6040)

idf_component_register(SRC_DIRS "." "hal"
                        INCLUDE_DIRS "include"
                        REQUIRES "${requires}" "esp_timer")