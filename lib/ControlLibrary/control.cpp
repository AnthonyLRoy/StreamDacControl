
#include "control.h"

namespace controlLibrary
{
    std::string control::GetName()
    {
        return "danny";
    };

    virtual esp_err_t control::ProcessEvent()
    {
    }
    
    virtual esp_err_t control::RegisterEvents()
    {
    }
} // namespace controlLibrary