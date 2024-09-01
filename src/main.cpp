


#include "main.h"
#include "Adafruit_MCP23017.h"
#include "Expander23018.h"
#include "handlers.h"
#include "driver/i2c.h"
#include "esp_log.h"
#include "I2Cbus.hpp"
#include <string>

#define MCP23017_IODIRA 0x00   // I/O Direction Register A
#define MCP23017_IODIRB 0x01   // I/O Direction Register B
#define MCP23017_GPIOA 0x12    // GPIO Register A
#define MCP23017_GPIOB 0x13    // GPIO Register B
#define MCP23017_GPINTENA 17 // Interrupt Enable Register A
#define MCP23017_GPINTENB 18 // Interrupt Enable Register B
#define MCP23018_OLAT 0x14
#define TAG "MCP"

Adafruit_MCP23017 ada;

// extern "C" void app_main(void)
// {
//     static main myMain;

//     // esp_event_loop_create_default();
//     nvs_flash_init();
//     gpio_install_isr_service(0);

//     // myMain.init_controls();
//     // myMain.RegisterEvents();

//     myMain.run();
// };

// void main::run()
// {

//     ESP_ERROR_CHECK(ada.init(GPIO_NUM_17, GPIO_NUM_18, 0x20, 10000, 0));
//     ESP_LOGI(TAG, "Starting I2C scanner...");
//     for (uint8_t addr = 0x03; addr <= 0x77; addr++) {
//         i2c_cmd_handle_t cmd = i2c_cmd_link_create();
//         i2c_master_start(cmd);
//         i2c_master_write_byte(cmd, (addr << 1) | I2C_MASTER_WRITE, true);
//         i2c_master_stop(cmd);
//         esp_err_t ret = i2c_master_cmd_begin(0, cmd, pdMS_TO_TICKS(1000));
//         i2c_cmd_link_delete(cmd);

//         if (ret == ESP_OK) {
//             ESP_LOGI(TAG, "Device found at address: 0x%02x", addr);
//         } else if (ret == ESP_ERR_TIMEOUT) {
//             ESP_LOGW(TAG, "Bus is busy or timeout: 0x%02x" , addr);
//         }
//     }
//     ESP_LOGI(TAG, "I2C scanning done.");
//     mcp23017_read_all_registers();
//     vTaskDelay(pdMS_TO_TICKS(5000));

//     while (true)
//     {

 
//         // Toggle the LED on GPIOA pin 0
//         ada.digitalWrite(MCP23017_OLATA, 0x01); // Turn on LED connected to GPIOA pin 0
//         vTaskDelay(pdMS_TO_TICKS(1000));        // Wait for 1 second

//         ada.digitalWrite(MCP23017_OLATA, 0x00); // Turn off LED
//         vTaskDelay(pdMS_TO_TICKS(1000));        // Wait for 1 second

//         // Read pin states
//        uint8_t res1 = ada.digitalRead(MCP23017_GPIOA);
//         ESP_LOGI(TAG, "GPIO state: 0x%02X", res1);
//     };
// };


extern "C" void app_main() {

     printf(">I2Cbus Example \n");
    fflush(stdout);

    I2C_t& myI2C = i2c0;  // i2c0 and i2c1 are the default objects
    
    ESP_ERROR_CHECK( myI2C.begin(GPIO_NUM_17, GPIO_NUM_18, 25000));
    myI2C.setTimeout(10);
    myI2C.scanner();

    myI2C.writeBit(0x69, 0x6B, 6, 0);
    
    uint8_t buffer[1];
    while (1) {
       esp_err_t r = myI2C.testConnection(0x20,1000);
       ESP_LOGI("connection","TEST RESULT %s",esp_err_to_name(r));
        ESP_LOGI("Test","testing Address");
        myI2C.writeByte(0x20,0x14,0xff);
        myI2C.readBytes(0x68, 0x14, 1, buffer);
        std::string header = std::to_string(buffer[1]);
        ESP_LOGI("result","RESULT IS : %s",header.c_str());
        vTaskDelay(1000 / portTICK_PERIOD_MS);

    }
    
    myI2C.close();
    vTaskDelay(portMAX_DELAY);
}
