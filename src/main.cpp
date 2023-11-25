#include "main.h"



extern "C" void app_main(void)
{
    static main myMain;

    esp_event_loop_create_default();
    nvs_flash_init();
}


esp_err_t main::run()
{

    //  register the event handlers

}