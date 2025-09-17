#include <avr/interrupt.h>
#include "switch_controller.h"

const int SwitchOne = 1;
const int SwitchTwo = 2;

SwitchController::SwitchController() : isSwitchOneClicked(false), isSwitchTwoClicked(false)
{
    // Set switch interrupt
    EICRB = (1 << ISC41) | (1 << ISC51);
    EIMSK = (1 << INT4) | (1 << INT5);
    PORTE = (1 << PE4) | (1 << PE5);
}

SwitchController& SwitchController::GetInstance()
{
    if (!instance) instance = new SwitchController();
    return *instance;
}

void SwitchController::DestroyInstance()
{
    delete instance;
    instance = nullptr;
}


void SwitchController::OnSwitchClick(Switch sw)
{
    switch (sw)
    {
    case Switch::One:
        isSwitchOneClicked = true;
        break;
    case Switch::Two:
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
        GameManager::GetInstance().SwitchClick(Switch::One);
        isSwitchOneClicked = false;
    }
    else if(isSwitchTwoClicked)
    {
        GameManager::GetInstance().SwitchClick(Switch::Two);
        isSwitchTwoClicked = false;
    }
}

SwitchController* SwitchController::instance = nullptr;



// Get switch 1 input
ISR(INT4_vect) 
{
    static SwitchController& switchController = SwitchController::GetInstance();

    if (!(PINE & (1 << PE4)))
        switchController.OnSwitchClick(Switch::One);
}


// Get switch 2 input
ISR(INT5_vect) 
{
    static SwitchController& switchController = SwitchController::GetInstance();

    if (!(PINE & (1 << PE5))) 
        switchController.OnSwitchClick(Switch::Two);
}