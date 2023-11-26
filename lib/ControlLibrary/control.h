#pragma once
#include "esp_log.h"
#include "esp_err.h"
#include "driver/gpio.h"
#include <string>


namespace controlLibrary
{

  class control
  {
    public:
        control();
        gpio_num_t virtual GetId();
        static void configure();
    private:
      gpio_num_t _id;
  };

} // namespace controlLibrary