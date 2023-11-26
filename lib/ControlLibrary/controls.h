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
         static esp_err_t  Add(control *newcontrol);
    };

    static std::map<uint16_t, controlLibrary::control> controlList;
};