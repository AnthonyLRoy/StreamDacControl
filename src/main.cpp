#include "main.h"
#include "button.h"
#include "handlers.h"
#include "Expander23018.h"

extern "C" void app_main(void)
{
    static main myMain;
    
    //esp_event_loop_create_default();
    //nvs_flash_init();
    gpio_install_isr_service(0);
    

    // myMain.init_controls();
    // myMain.RegisterEvents();

myMain.run();
};

esp_err_t main::run()
{
   
    ESP_LOGI("Test", "Starting Init");
    static Expander23018 exp;
    exp.init(GPIO_NUM_7,GPIO_NUM_15,21,100000,0);

    //  register the event handlers
    while (true) {
        // Toggle pin 0
        exp.mcp23018_write_register(0x14, 0x01);
        vTaskDelay(pdMS_TO_TICKS(500));
        exp.mcp23018_write_register(0x14, 0x00);
        vTaskDelay(pdMS_TO_TICKS(500));

        // Read pin states
        uint8_t gpio_state;
        exp.mcp23018_read_register(0x12, &gpio_state);
        ESP_LOGI("Test", "GPIO state: 0x%02X", gpio_state);
    }
};

esp_err_t main::init_controls()
{
       controlLibrary::control* control =  new controlLibrary::control();
       controlLibrary::controls::Add(control);
       gpio_isr_handler_add(control->GetId(),handlers::buttonHandler::button_isr_handler, (void*)control);

    //   controlLibrary::control* fred = new streamerControls::GenericButton("ButtonID",controlLibrary::BUTTON_NEXT,GPIO_INTR_POSEDGE);
    return ESP_OK;
};

esp_err_t main::RegisterEvents()
{
    return ESP_OK;
};
