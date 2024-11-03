#pragma once

#include "driver/uart.h"
#include "esp_log.h"
#include <string.h>
#include "esp_err.h"


namespace serialbus
{

    class SERIAL;
}


namespace serialbus
{

    class SERIAL
    {
    public:
     void init_uart(int baudRate, uart_port_t UART_NUM,uint bufferSize,int TX_PIN,uint RX_PIN);
     void send_data( const char* message);
     int read_data(char* buffer , size_t buffer_size);
    private:
      uart_port_t uart_number;
    };

}