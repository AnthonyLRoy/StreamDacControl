#pragma once
#include "actions.h"


class InputAction : actions::ActionBase
{
    public:
        using actions::ActionBase::ActionBase;
        void Handle();

};