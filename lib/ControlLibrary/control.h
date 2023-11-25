#pragma once
#include "esp_log.h"
#include <string>
#include "eventType.h"

namespace controlLibrary
{

class control
{
  public:
    std::string GetName();
    virtual esp_err_t ProcessEvent();
    virtual esp_err_t RegisterEvents();
};

} // namespace controlLibrary