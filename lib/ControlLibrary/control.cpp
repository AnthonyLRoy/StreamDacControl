
#include "control.h"

namespace controlLibrary
{

    control::control::control control::control()
    {
        return this;
    }
    gpio_num_t control::GetId()
    {
        return _id;
    };


} // namespace controlLibrary