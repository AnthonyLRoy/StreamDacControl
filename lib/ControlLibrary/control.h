#pragma once
#include "esp_log.h"
#include "esp_err.h"
#include <string>


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