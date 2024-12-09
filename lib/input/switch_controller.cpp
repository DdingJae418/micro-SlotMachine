#include <avr/interrupt.h>
#include "switch_controller.h"

const int SWITCH_ONE = 1;
const int SWITCH_TWO = 2;

SwitchController::SwitchController() : isSwitchOneClicked(false), isSwitchTwoClicked(false)
{
    // Set switch interrupt
    EICRB = (1 << ISC41) | (1 << ISC51);
    EIMSK = (1 << INT4) | (1 << INT5);
    PORTE = (1 << PE4) | (1 << PE5);
}

SwitchController& SwitchController::GetInstance()
{
    static SwitchController instance;
    return instance;
}


void SwitchController::OnSwitchClick(Switch sw)
{
    switch (sw)
    {
    case Switch::ONE:
        isSwitchOneClicked = true;
        break;
    case Switch::TWO:
        isSwitchTwoClicked = true;
        break;
    default:
        break;
    }
}

void SwitchController::Update()
{
    if(isSwitchOneClicked)
    {
        GameManager::GetInstance().SwitchClick(Switch::ONE);
        isSwitchOneClicked = false;
    }
    else if(isSwitchTwoClicked)
    {
        GameManager::GetInstance().SwitchClick(Switch::TWO);
        isSwitchTwoClicked = false;
    }
}



// Get switch 1 input
ISR(INT4_vect) 
{
    static SwitchController& switchController = SwitchController::GetInstance();

    if (!(PINE & (1 << PE4)))
        switchController.OnSwitchClick(Switch::ONE);
}


// Get switch 2 input
ISR(INT5_vect) 
{
    static SwitchController& switchController = SwitchController::GetInstance();

    if (!(PINE & (1 << PE5))) 
        switchController.OnSwitchClick(Switch::TWO);
}