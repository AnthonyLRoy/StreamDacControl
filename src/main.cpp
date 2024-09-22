#include "main.h"
#include "handlers.h"
#include "freertos/task.h"
#include "I2Cbus.hpp"
#include "spi.hpp"
#include "driver/gpio.h"
#include <string>
#include "string.h"
#include "driver/ledc.h"

#define PIN_APP_ACTIVE_LED GPIO_NUM_48
#define PIN_SPI_SDO GPIO_NUM_7
#define PIN_SPI_CLK GPIO_NUM_6

#define HSPI_HOST SPI2_HOST
#define TAG "MCP"

#define PIN_ON_LED GPIO_NUM_3
#define PIN_STANBY_LED GPIO_NUM_46

#define PIN_LATCH_ENABLE GPIO_NUM_5 // Chip Select (CS)

#define PIN_ENABLE_I2C GPIO_NUM_17

extern "C" void app_main(void)
{
    static main myMain;
    // esp_event_loop_create_default();
    nvs_flash_init();
    gpio_install_isr_service(0);
    myMain.run();
}

void main::run()
{

    printf(">I2Cbus Example \n");
    fflush(stdout);
    I2C_t &myI2C = i2c0; // i2c0 and i2c1 are the default objects
    SPI_t &mySPI = spi2;

    // indicator leds
    gpio_set_direction(PIN_APP_ACTIVE_LED, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_ON_LED, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_STANBY_LED, GPIO_MODE_OUTPUT);

    // Test I2C connection and scan for Channel

    ESP_ERROR_CHECK(myI2C.begin(GPIO_NUM_16, GPIO_NUM_15, 50000));
    myI2C.setTimeout(10);
    myI2C.scanner();
    esp_err_t r = myI2C.testConnection(0x20, 1000);

    // Setup SPI for leds

    gpio_set_direction(PIN_SPI_SDO, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_SPI_CLK, GPIO_MODE_OUTPUT);
    
    gpio_set_direction(PIN_LATCH_ENABLE, GPIO_MODE_OUTPUT);
   gpio_set_direction(GPIO_NUM_17, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_17, 1);
    mySPI.spi_init(PIN_SPI_SDO, PIN_SPI_CLK);

    esp_rom_gpio_pad_select_gpio(PIN_LATCH_ENABLE);


    gpio_set_level(PIN_LATCH_ENABLE, 0);

    uint8_t buffer[1] = {0x1};
    uint8_t cntr = 0;

    while (1)
    {

        // I2C test Write bytes to I2C address
        myI2C.writeByte(MCP23017_ADDRESS, MCP23017_OLATB, cntr);
        myI2C.writeByte(MCP23017_ADDRESS, MCP23017_OLATA, cntr);

        // test write to spi connection

        mySPI.spi_send_only(0xAAAA);
        mySPI.pulseLatchEnable(PIN_LATCH_ENABLE);

        // standby leds
        gpio_set_level(PIN_STANBY_LED, 0);
        gpio_set_level(PIN_ON_LED, 1);

        vTaskDelay(500 / portTICK_PERIOD_MS);

        // Test can read back change on I2C port
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

        cntr++;
        cntr = cntr % 0xff;

        // swap leds
        gpio_set_level(PIN_STANBY_LED, 1);
        gpio_set_level(PIN_ON_LED, 0);

        mySPI.spi_send_only(0x5555);
        mySPI.pulseLatchEnable(PIN_LATCH_ENABLE);

        vTaskDelay(500 / portTICK_PERIOD_MS);
    }

    myI2C.close();
    vTaskDelay(portMAX_DELAY);
};
