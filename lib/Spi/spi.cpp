#include "spi.hpp"
#include <esp32c2/rom/ets_sys.h>
#include "freertos/task.h"

SPI_t spi2 = spibus::SPI(SPI2_HOST);

namespace spibus
{
    spi_device_handle_t spi;
    gpio_num_t sdo;
    gpio_num_t clk;
    spi_host_device_t host;

    void SPI::spi_init(gpio_num_t serial_data_out, gpio_num_t data_clock_out)
    {
        sdo = serial_data_out;
        clk = data_clock_out;
        esp_err_t ret;

        // Configuration for the SPI bus
        spi_bus_config_t buscfg = {
            .mosi_io_num = sdo,
            .miso_io_num = -1, // No MISO since it's receive-only
            .sclk_io_num = clk,
            .quadwp_io_num = -1,
            .quadhd_io_num = -1,
            .max_transfer_sz = 4096,
        };

        // Initialize the SPI bus
        ret = spi_bus_initialize(host, &buscfg, SPI_DMA_CH_AUTO); // 1 indicates DMA channel
        ESP_ERROR_CHECK(ret);

        // Configuration for the SPI device
        spi_device_interface_config_t devcfg = {
            .clock_speed_hz = 1 * 1000 * 1000, // 1 MHz clock speed

            // CS pin
            .queue_size = 1,
        };

        // Attach the SPI device to the SPI bus
        ret = spi_bus_add_device(host, &devcfg, &spi);
        ESP_ERROR_CHECK(ret);
    }

    void SPI::spi_send_only(uint16_t dataToSend)
    {
        esp_err_t ret;

        // Create a transaction to send data (no receive buffer)
        spi_transaction_t t;
        memset(&t, 0, sizeof(t));      // Zero out the transaction structure
        uint16_t tx_data = dataToSend; // Example data to send (0x55)
        t.length = 8;                  // Transaction length in bits
        t.tx_buffer = &tx_data;        // Pointer to data to send

        // Perform the SPI transaction (send-only)
        ret = spi_device_transmit(spi, &t); // Blocking call to transmit data
        ESP_ERROR_CHECK(ret);

        ESP_LOGI(TAG, "Data sent: 0x%x", tx_data);
    }
    void SPI::pulseLatchEnable(gpio_num_t gpioPin)
    {
            gpio_set_level(gpioPin, 1);
            vTaskDelay(1 / portTICK_PERIOD_MS);
            gpio_set_level(gpioPin, 0);
    }
    SPI::SPI(spi_host_device_t spi_host)
    {
        host = spi_host;
    }

    SPI::~SPI()
    {
    }

}
