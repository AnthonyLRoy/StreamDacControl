#include "main.h"
#include "Adafruit_MCP23017.h"
#include "Expander23018.h"
#include "button.h"
#include "handlers.h"

#define MCP23017_IODIRA 0x00   // I/O Direction Register A
#define MCP23017_IODIRB 0x01   // I/O Direction Register B
#define MCP23017_GPIOA 0x12    // GPIO Register A
#define MCP23017_GPIOB 0x13    // GPIO Register B
#define MCP23017_GPINTENA 0x04 // Interrupt Enable Register A
#define MCP23017_GPINTENB 0x05 // Interrupt Enable Register B
#define MCP23018_OLAT 0x14
#define TAG "MCP"
extern "C" void app_main(void)
{
    static main myMain;

    // esp_event_loop_create_default();
    nvs_flash_init();
    gpio_install_isr_service(0);

    // myMain.init_controls();
    // myMain.RegisterEvents();

    myMain.run();
};

void main::run()
{
    Adafruit_MCP23017 ada;
    vTaskDelay(pdMS_TO_TICKS(5000));
    ESP_ERROR_CHECK(ada.init(GPIO_NUM_4, GPIO_NUM_5, 0x20, 100000, 0));
    ada.digitalWrite(MCP23017_OLATA, 0x01);
    uint8_t resut = ada.digitalRead(MCP23017_OLATA);
    ESP_LOGI("Test", "result ada 0x%02X", resut);

    for (uint8_t address = 1; address < 127; address++)
    {
        i2c_cmd_handle_t cmd = i2c_cmd_link_create();
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_WRITE, true);
        i2c_master_stop(cmd);
        esp_err_t ret = i2c_master_cmd_begin(0, cmd, pdMS_TO_TICKS(1000));
        i2c_cmd_link_delete(cmd);
        if (ret == ESP_OK)
        {
            ESP_LOGI("I2C Scanner", "Found device at address: 0x%02X", address);
        }
        else if (ret == ESP_ERR_TIMEOUT)
        {
            ESP_LOGW("I2C Scanner", "Timeout at address: 0x%02X", address);
        }
    };

    while (true)
    {
        ada.digitalWrite(MCP23018_OLAT, 0xFF);
        vTaskDelay(pdMS_TO_TICKS(1000));
        ada.digitalWrite(MCP23018_OLAT, 0x00);
        vTaskDelay(pdMS_TO_TICKS(1000));

        // Read pin states
        uint8_t gpio_state;
        uint8_t res = ada.digitalRead(0x12);
        ESP_LOGI(TAG, "GPIO state: 0x%02X", res);
    };
};

esp_err_t main::init_controls()
{
    controlLibrary::control *control = new controlLibrary::control();
    controlLibrary::controls::Add(control);
    gpio_isr_handler_add(control->GetId(), handlers::buttonHandler::button_isr_handler, (void *)control);
    return ESP_OK;
};

esp_err_t main::RegisterEvents()
{
    return ESP_OK;
};
