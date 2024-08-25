#pragma once
#include "controls.h"
#include "driver\gpio.h"

namespace streamerControls
{
    class GenericButton : public controlLibrary::control
    {
        public:
            GenericButton(std::string name, controlLibrary::eventName eventManaged, gpio_int_type_t eventType);
    };
 
    class RotaryEncoder : public controlLibrary::control
    {
        public:
            RotaryEncoder(std::string name, controlLibrary::eventName eventManaged, gpio_int_type_t eventTypeA, gpio_int_type_t eventTypeB );
    };

    class Output :public controlLibrary::control
    {
        public:
            Output(std::string name, controlLibrary::eventName eventManaged, gpio_int_type_t eventTypeA );
 
    };

};