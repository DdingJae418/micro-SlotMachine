#ifndef BUZZER_CONTROLLER_H
#define BUZZER_CONTROLLER_H

#include <fixed_rate_updater.h>

class BuzzerController : public UpdateListener
{
public:
    virtual void Update();
};


#endif