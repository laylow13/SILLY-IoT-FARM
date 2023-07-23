#include "i2c_bus.h"
#include <iostream>
#include "usr_sensors.h"
#include "usr_motor.h"
#include "usr_light.h"
#include "usr_gui.h"
#include "usr_cloud_service.h"
#include "esp_log.h"
#include "nvs_flash.h"

extern "C" void app_main(void) {
    usr::rainmaker_init();
    usr::gui_task_create();
    usr::sensors_task_create();
    usr::motor_task_create();
    usr::light_task_create();
}