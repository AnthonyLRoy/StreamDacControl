#pragma once
#include "esp_log.h"
#include "control.h"
#include <map>

namespace controlLibrary
{

    class controls
    {
        public:
         controls(void) {};
         int  Add();
    };

    static std::map<uint16_t, controlLibrary::control> controlList;
};