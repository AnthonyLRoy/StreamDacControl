#pragma once
#include "driver\i2c.h"

class Expander23018
{

  public:
   esp_err_t init(gpio_num_t sda, gpio_num_t scl, int address, int freq, i2c_port_t portnumber);
   esp_err_t mcp23018_write_register(uint8_t reg, uint8_t value);
   esp_err_t mcp23018_read_register(uint8_t reg, uint8_t * data);
   esp_err_t GetStatus();
   private:
   
  private:
   esp_err_t i2c_master_init();
    gpio_num_t _sda;
    gpio_num_t _scl;
    int _address ;
    int _freq ;
    i2c_port_t _portNumber;
    esp_err_t  _status = ESP_ERR_INVALID_ARG;

};