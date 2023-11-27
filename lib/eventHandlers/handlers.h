#pragma once 
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

namespace  handlers
{
    class buttonHandler
    {
    public:
        static void button_isr_handler(void *params);
    };
} // handlers namespace name

