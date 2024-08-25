
#include "button.h"
namespace streamerControls
{
    GenericButton::GenericButton(std::string name, controlLibrary::eventName eventManaged, gpio_int_type_t eventType){};

    RotaryEncoder::RotaryEncoder(std::string name, controlLibrary::eventName eventManaged, gpio_int_type_t eventTypeA,
                                gpio_int_type_t eventTypeB){};

    Output::Output(std::string name, controlLibrary::eventName eventManaged, gpio_int_type_t eventType){}

}; // namespace streamerControls
