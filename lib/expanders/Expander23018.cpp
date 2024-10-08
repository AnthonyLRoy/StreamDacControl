#include "Expander23018.h"
#include "esp_log.h"
#define I2C_MASTER_NUM I2C_NUM_0
#define MCP23018_GPIO 0x12
#define MCP23018_OLAT 0x14
//static const char *TAG = "MCP23018";

    esp_err_t Expander23018::init(gpio_num_t sda, gpio_num_t scl, int address, int freq, i2c_port_t portnumber)
    {
        
        _sda =sda;
        _scl = scl;
        _freq = freq;
        _address = address;
        ESP_LOGI("Test", "Starting Initiation");
        esp_err_t result = i2c_master_init();
        if (result != ESP_OK)
        {
                ESP_LOGI("Test", "Failed to Init I2C connection  ");
        }
        ESP_LOGI("Test", "completed ");
        _status = result;
        return result;
    }

    esp_err_t Expander23018::mcp23018_write_register(uint8_t reg, uint8_t value)
    {
        ESP_LOGI("Test", "Write  address ");
        i2c_cmd_handle_t cmd = i2c_cmd_link_create();
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, (_address << 1) | I2C_MASTER_WRITE, 1);
        i2c_master_write_byte(cmd, reg, 1);
        i2c_master_write_byte(cmd, value, 1);
        //i2c_master_stop(cmd);
        esp_err_t ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, pdMS_TO_TICKS(1000));
        if (ret != ESP_OK)
        {
             ESP_LOGI("Test", "Write Failed %s",esp_err_to_name(ret));
        }
        i2c_cmd_link_delete(cmd);
        return ret;
    };

    esp_err_t Expander23018::mcp23018_read_register(uint8_t reg, uint8_t *data)
    {
                ESP_LOGI("Test", "read  ");
        i2c_cmd_handle_t cmd = i2c_cmd_link_create();
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, (_address << 1) | I2C_MASTER_WRITE, 1);
        i2c_master_write_byte(cmd, reg, 1);
        i2c_master_stop(cmd);
        esp_err_t ret = i2c_master_cmd_begin(_portNumber, cmd, pdMS_TO_TICKS(1000));
        if (ret != ESP_OK)
        { 
          ESP_LOGI("Test", "read Register Failed %s",esp_err_to_name(ret));   
        }
        i2c_cmd_link_delete(cmd);
        return ret;
    }

    esp_err_t Expander23018::GetStatus()
    {
        return _status;

    }

    esp_err_t Expander23018::i2c_master_init()
    {

        ESP_LOGI("Test", "Starting master init  ");
        i2c_config_t conf;
        conf.mode = I2C_MODE_MASTER;
        conf.sda_io_num = _sda;
        conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
        conf.scl_io_num = _scl;
        conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
        conf.master.clk_speed = _freq;
        conf.clk_flags = 0;
        i2c_param_config(I2C_MASTER_NUM, &conf);
        return i2c_driver_install(_portNumber, conf.mode, 0, 0, 0);
    };

