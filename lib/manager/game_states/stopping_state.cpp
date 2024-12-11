#include <fnd_controller.h>
#include <buzzer_controller.h>
#include <game_enums.h>
#include "game_states.h"


StoppingState::StoppingState(GameManager& gm, FNDController& fnd, BuzzerController& buzzer)
    : gm(gm), fnd(fnd), buzzer(buzzer)
{ }

void StoppingState::StartState()
{
    // Set variables
    time = 0;
    phase = 0;
}

void StoppingState::UpdateState()
{   

}


void StoppingState::SwitchOne() { }
void StoppingState::EndState() { }
void StoppingState::SwitchTwo() { }