#pragma once
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "control.h"

namespace handlers
{
    class rotary_controller_left :  controlLibrary::control
    {
        public:
            static void configure(); 
            static void handle();
        };
    class button_select :  controlLibrary::control
    {
        public:
            static void configure();
            static void handle();
        };
    class button_back :  controlLibrary::control
    {
        public:
            static void configure();
            static void handle();
    };
    class button_on_off :  controlLibrary::control
    {
        public:
            static void configure();
            static void handle();
    };
    class button_play :  controlLibrary::control
    {
        public:
            static void configure();
            static void handle();
    };
    class button_pause :  controlLibrary::control
    {
        public:
            static void configure();
            static void handle();
    };
    class button_next :  controlLibrary::control
    {
        public:
            static void configure();
            static void handle();
    };

    class button_previous :  controlLibrary::control
    {
        public:
            static void configure();
            static void handle();
    };

} // namespace handlers
