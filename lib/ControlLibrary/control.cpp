
#include "control.h"

namespace controlLibrary
{
    std::string control::GetName()
    {
        return "danny";
    };

    esp_err_t control::ProcessEvent()
    {
        return ESP_ERR_NOT_SUPPORTED;
    };
    
    esp_err_t control::RegisterEvents()
    { 
        return ESP_ERR_NOT_SUPPORTED;
    };
    
} // namespace controlLibrary