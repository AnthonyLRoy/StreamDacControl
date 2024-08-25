#include "control.h"
namespace controlLibrary
{

    control::control()
    {

    }
    gpio_num_t control::GetId()
    {
        return _id;
    };
} // namespace controlLibrary