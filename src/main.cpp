


#include "main.h"
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

    I2C_t& myI2C = i2c0;  // i2c0 and i2c1 are the default objects
    
    ESP_ERROR_CHECK( myI2C.begin(GPIO_NUM_17, GPIO_NUM_18, 100000));
    myI2C.setTimeout(10);
    myI2C.scanner();
    esp_err_t r = myI2C.testConnection(0x20,1000);
 
    uint8_t buffer[1] ={ 0x1};
    myI2C.writeByte(MCP23017_ADDRESS,MCP23017_IODIRA,0x00);
    myI2C.writeByte(MCP23017_ADDRESS,MCP23017_IODIRB,0x00);

    myI2C.writeByte(MCP23017_ADDRESS,MCP23017_OLATB,0xff);
    myI2C.writeByte(MCP23017_ADDRESS,MCP23017_OLATA,0xff);

    myI2C.writeByte(MCP23017_ADDRESS,MCP23017_IODIRA,0x00);
    myI2C.writeByte(MCP23017_ADDRESS,MCP23017_IODIRB,0x00);

    uint8_t cnt =0;
    while (1) {


        vTaskDelay(1000 / portTICK_PERIOD_MS);
    myI2C.writeByte(MCP23017_ADDRESS,MCP23017_OLATB,0xff);
    myI2C.writeByte(MCP23017_ADDRESS,MCP23017_OLATA,0xff);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        myI2C.writeByte(MCP23017_ADDRESS,MCP23017_OLATB,0x00);
    myI2C.writeByte(MCP23017_ADDRESS,MCP23017_OLATA,0x00); 
        
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
