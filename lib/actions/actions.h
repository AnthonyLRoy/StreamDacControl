#pragma once
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "control.h"

namespace actions
{
    class rotary_controller_left 
    {
        public:
            static void handle();
        };
    class button_select 
    {
        public:
            static void configure();
            static void handle();
        };
    class button_back 
    {
        public:
            static void configure();
            static void handle();
    };
    class button_on_off 
    {
        public:
            static void handle();
    };
    class button_play 
    {
        public:
            static void handle();
    };
    class button_pause 
    {
        public:
            static void handle();
    };
    class button_next 
    {
        public:
            static void handle();
    };

    class button_previous 
    {
        public:

            static void handle();
    };

} // namespace handlers
