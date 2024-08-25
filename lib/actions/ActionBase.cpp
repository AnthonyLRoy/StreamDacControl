#pragma once

#include "actionBase.h"


//base class for all actions 

namespace actions
{
class ActionBase
{
  public:
    ActionBase(int id, std::string name)
    {
        setId(id);
        SetName(name);
        int getId()
        {
            return Id;
        }
        std::string getName()
        {
            return Name;
        }

    }
    void Handle();

  private:
    int Id;
    std::string Name;

    void setId(int id)
    {
        // Check does IDAlreadyExist
        Id = id;
    }
    void SetName(std::string name)
    {
        // check if name alredy exists
        Name = name;
    }
};


} // namespace actions
