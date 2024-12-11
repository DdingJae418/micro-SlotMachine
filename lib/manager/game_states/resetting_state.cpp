#include <fnd_controller.h>
#include <buzzer_controller.h>
#include <game_enums.h>
#include "game_states.h"


ResettingState::ResettingState(GameManager& gm, FNDController& fnd, BuzzerController& buzzer)
    : gm(gm), fnd(fnd), buzzer(buzzer)
{ }

void ResettingState::StartState()
{
    // Set variables
    time = 0;
    phase = 0;
}

void ResettingState::UpdateState()
{   

}


void ResettingState::SwitchOne() { }
void ResettingState::EndState() { }
void ResettingState::SwitchTwo() { }