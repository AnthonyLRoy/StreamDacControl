
#pragma once
#include "esp_err.h"
#include "esp_log.h"
#include <hal/spi_types.h>
#include "driver/spi_master.h"
#include "esp_mac.h"
#include "driver/gpio.h"
#include "string.h"

namespace spibus
{

#define TAG "SPI"
    class SPI;
}

using SPI_t = spibus::SPI;

// default spi interface
extern SPI_t spi2;

namespace spibus
{
    class SPI
    {
        private:
            gpio_num_t sdo;
            gpio_num_t sco;
            spi_device_handle_t spi;

        public:
            explicit SPI(spi_host_device_t api_host);
            ~SPI();
            void spi_init(gpio_num_t sdi, gpio_num_t clck);
            void spi_send_only(uint16_t data);
    };
}
