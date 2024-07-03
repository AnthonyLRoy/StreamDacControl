
#include "handlers.h"


namespace handlers
{

    QueueHandle_t actionEventQueue = xQueueCreate(10, sizeof(uint32_t));
    QueueHandle_t radioButtonQueue = xQueueCreate(10, sizeof(uint32_t));


    void buttonHandler::button_isr_handler(void *params)
    {
        uint32_t button_id = (uint32_t)params;
        xQueueSendFromISR(radioButtonQueue, &button_id, NULL);
    };
/*
static int state;
     bool debounce() {
      state = (state<<1) | digitalRead(btn) | 0xfe00;
      return (state == 0xff00);
    }
*/
} // namespace handlers
