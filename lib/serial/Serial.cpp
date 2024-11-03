#include "Serial.hpp"

void serialbus::SERIAL::init_uart(int baudRate, uart_port_t UART_NUM, uint bufferSize, int TX_PIN, uint RX_PIN)
{

    uart_number = UART_NUM;

    uart_config_t uart_config = {
        .baud_rate = baudRate, // Set your baud rate here
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };

    ESP_ERROR_CHECK(uart_driver_install(UART_NUM, bufferSize * 2, 0, 0, NULL, 0));
    ESP_ERROR_CHECK(uart_param_config(UART_NUM, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(UART_NUM, TX_PIN, RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
}

void serialbus::SERIAL::send_data(const char *message)
{

    int len = strlen(message);   // Get the length of the string
    uart_write_bytes(uart_number, message, len);  // Send the string
}

int serialbus::SERIAL::read_data(char *buffer, size_t buffer_size)
{
    int length = uart_read_bytes(uart_number, (uint8_t *)buffer, buffer_size, 100 / portTICK_PERIOD_MS); // 100ms timeout

    if (length > 0)
    {
        buffer[length] = '\0'; // Null-terminate the buffer to make it a proper string
    }
    else
    {
        buffer[0] = '\0'; // If no data, make the buffer an empty string
    }

    return length;
}
