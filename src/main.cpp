#include "main.h"
#include "controls.h"

extern "C" void app_main(void)
{
    static main myMain;

    esp_event_loop_create_default();
    nvs_flash_init();
    gpio_install_isr_service(0);
    

    myMain.init_controls();
    myMain.RegisterEvents();

    while (true)
    {
        myMain.run();
    };
};

esp_err_t main::run()
{
    //  register the event handlers
    return ESP_OK;
    vTaskDelay(100);
};

esp_err_t main::init_controls()
{
      //controlLibrary::control* fred = new streamerControls::GenericButton(GPIO_NUM_17,controlLibrary::BUTTON_NEXT,GPIO_INTR_POSEDGE);
    return ESP_OK;
};

esp_err_t main::RegisterEvents()
{
    return ESP_OK;
};
