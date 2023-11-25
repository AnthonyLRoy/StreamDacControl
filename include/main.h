#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "driver\gpio.h"


class main final
{
    public:
        esp_err_t run();
        esp_err_t init_controls();
        esp_err_t RegisterEvents();
};



