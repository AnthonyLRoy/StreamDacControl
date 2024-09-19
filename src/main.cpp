#include "main.h"
#include "Expander23018.h"
#include "handlers.h"
#include "driver/i2c.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "I2Cbus.hpp"


#include "driver/gpio.h"
#include <string>
#include "driver/spi_master.h"
#include "string.h"
#include <hal/spi_types.h>
#define HSPI_HOST SPI2_HOST
#define TAG "MCP"

#define PIN_NUM_MISO -1  // No MISO (receive-only slave)
#define PIN_NUM_MOSI 7  // SPI MOSI
#define PIN_NUM_CLK  6  // SPI Clock
#define PIN_NUM_CS   5   // Chip Select (CS)

extern "C" void app_main(void)
{
    static main myMain;
    // esp_event_loop_create_default();
    nvs_flash_init();
    gpio_install_isr_service(0);
    myMain.run();
}

spi_device_handle_t spi;

void spi_init() {
    esp_err_t ret;

    // Configuration for the SPI bus
    spi_bus_config_t buscfg = {
        .miso_io_num = PIN_NUM_MISO,  // No MISO since it's receive-only
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4096,
    };

    // Initialize the SPI bus
    ret = spi_bus_initialize(HSPI_HOST, &buscfg,SPI_DMA_CH_AUTO);  // 1 indicates DMA channel
    ESP_ERROR_CHECK(ret);

    // Configuration for the SPI device
    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 1 * 1000 * 1000,  // 1 MHz clock speed
   
              // CS pin
        .queue_size = 1,
    };

    // Attach the SPI device to the SPI bus
    ret = spi_bus_add_device(HSPI_HOST, &devcfg, &spi);
    ESP_ERROR_CHECK(ret);
}

void spi_send_only() {
    esp_err_t ret;

    // Create a transaction to send data (no receive buffer)
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));               // Zero out the transaction structure
    uint8_t tx_data = 0x55;                 // Example data to send (0x55)
    t.length = 8;                           // Transaction length in bits
    t.tx_buffer = &tx_data;                 // Pointer to data to send

    // Perform the SPI transaction (send-only)
    ret = spi_device_transmit(spi, &t);     // Blocking call to transmit data
    ESP_ERROR_CHECK(ret);

    ESP_LOGI(TAG, "Data sent: 0x%x", tx_data);
}



void main::run()
{

    printf(">I2Cbus Example \n");
    fflush(stdout);
    I2C_t &myI2C = i2c0; // i2c0 and i2c1 are the default objects
    gpio_set_direction(GPIO_NUM_48, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_17,GPIO_MODE_OUTPUT);
   gpio_set_level(GPIO_NUM_17,1);


    gpio_set_level(GPIO_NUM_48, 1);
    ESP_ERROR_CHECK(myI2C.begin(GPIO_NUM_16, GPIO_NUM_15, 50000));
    myI2C.setTimeout(10);
    myI2C.scanner();
    esp_err_t r = myI2C.testConnection(0x20, 1000);
    spi_init();

    uint8_t buffer[1] = {0x1};
    myI2C.writeByte(MCP23017_ADDRESS, MCP23017_IODIRA, 0x00);
    myI2C.writeByte(MCP23017_ADDRESS, MCP23017_IODIRB, 0x00);

    myI2C.writeByte(MCP23017_ADDRESS, MCP23017_OLATB, 0xff);
    myI2C.writeByte(MCP23017_ADDRESS, MCP23017_OLATA, 0xff);

    myI2C.writeByte(MCP23017_ADDRESS, MCP23017_IODIRA, 0x00);
    myI2C.writeByte(MCP23017_ADDRESS, MCP23017_IODIRB, 0x00);

    uint8_t cnt = 0;
    while (1)
    {
        spi_send_only();
        gpio_set_level(GPIO_NUM_48, 1);

        vTaskDelay(1000 / portTICK_PERIOD_MS);
        myI2C.writeByte(MCP23017_ADDRESS, MCP23017_OLATB, 0xff);
        myI2C.writeByte(MCP23017_ADDRESS, MCP23017_OLATA, 0xff);

        esp_err_t res = myI2C.readByte(0x20, MCP23017_OLATA, buffer);
        if (res != ESP_OK)
        {
            ESP_LOGW("FAIL", "READ FAILED %s ", esp_err_to_name(res));
        }
        else
        {
            std::string header = std::to_string(buffer[0]);
            ESP_LOGI("result", "RESULT A IS : %s", header.c_str());
        }
vTaskDelay(100 / portTICK_PERIOD_MS);



        gpio_set_level(GPIO_NUM_48, 0);
        vTaskDelay(100 / portTICK_PERIOD_MS);

        gpio_set_level(GPIO_NUM_48, 1);

        myI2C.writeByte(MCP23017_ADDRESS, MCP23017_OLATB, 0x00);
        myI2C.writeByte(MCP23017_ADDRESS, MCP23017_OLATA, 0x00);
  esp_err_t res2 = myI2C.readByte(0x20, MCP23017_IOCONB, buffer);
        if (res != ESP_OK)
        {
            ESP_LOGW("FAIL", "READ FAILED %s ", esp_err_to_name(res2));
        }
        else
        {
            std::string header = std::to_string(buffer[0]);
            ESP_LOGI("result", "RESULT B IS : %s", header.c_str());
        }
        // ESP_LOGI("Test","testing Address 0x%X ", cnt);

        // esp_err_t res = myI2C.readByte(0x20,cnt++, buffer);
        // if (res != ESP_OK)
        // {
        //     ESP_LOGW("FAIL","READ FAILED %s ",esp_err_to_name(res) );
        // }
        // std::string header = std::to_string(buffer[0]);
        // ESP_LOGI("result","RESULT IS : %s",header.c_str());
        // vTaskDelay(1000 / portTICK_PERIOD_MS);
        // if (cnt  > 21) {cnt = 0;};
    }

    myI2C.close();
    vTaskDelay(portMAX_DELAY);
};

// extern "C" void app_main() {

//      printf(">I2Cbus Example \n");
//     fflush(stdout);

//     I2C_t& myI2C = i2c0;  // i2c0 and i2c1 are the default objects

//     ESP_ERROR_CHECK( myI2C.begin(GPIO_NUM_17, GPIO_NUM_18, 100000));
//     myI2C.setTimeout(10);
//     myI2C.scanner();

//     myI2C.writeBit(0x20, 0x12, 6, 0);
//     myI2C.writeByte(0x20,0x14,0x05);
//     uint8_t buffer[1];
//     uint8_t cnt =0;
//     while (1) {
//        esp_err_t r = myI2C.testConnection(0x20,1000);
//        ESP_LOGI("connection","TEST RESULT %s",esp_err_to_name(r));
//         ESP_LOGI("Test","testing Address");

//         esp_err_t res = myI2C.readBytes(0x20, 0x12, 1, buffer);
//         if (res != ESP_OK)
//         {
//             ESP_LOGW("FAIL","READ FAILED %s ",esp_err_to_name(res) );
//         }
//         std::string header = std::to_string(buffer[0]);
//         ESP_LOGI("result","RESULT IS : %s",header.c_str());
//         vTaskDelay(1000 / portTICK_PERIOD_MS);

//     }

//     myI2C.close();
//     vTaskDelay(portMAX_DELAY);
// }
