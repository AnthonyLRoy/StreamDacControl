#pragma once
#include "control.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"

namespace actions
{

class ActionBase
{
  public:
    ActionBase(int id, std::string name);
    void Handle();
    int getId();
    std::string getName();

  private:
    void setId(int id);
    void SetName(std::string name);
};

} // namespace actions
