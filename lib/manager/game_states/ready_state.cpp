#include <fnd_controller.h>
#include <buzzer_controller.h>
#include <game_enums.h>
#include "game_states.h"

const float ANIMATION_SPEED = 30;
const float WAITING_TIME = 0.9;


ReadyState::ReadyState(GameManager& gm, FNDController& fnd, BuzzerController& buzzer)
    : gm(gm), fnd(fnd), buzzer(buzzer)
{ }

void ReadyState::StartState()
{
    // Set variables
    time = 0;
    phase = 0;

    // Empty FND display
    fnd.SetDisplay(Letter::NONE, false);
    fnd.StartAnimation(Animation::NONE);

    // Play ready sound
    buzzer.StartSound(&sounds::READY_SONG, 2.2, true);
}

void ReadyState::UpdateState()
{
    if(fnd.IsAnimationPlaying()) return;
    
    if(phase == 0)
    {
        // Set 'PLAY' letter and start 'SWIPE' animation at the FND display
        fnd.SetDisplay(Letter::PLAY);
        fnd.StartAnimation(Animation::SWIPE, ANIMATION_SPEED);
        phase++;
    }
    else
    {
        // Count second
        time += Time::DeltaTime();

        // Swipe out 'PLAY' letter
        if(time > WAITING_TIME)
        {
            fnd.SetDisplay(Letter::NONE);
            fnd.StartAnimation(Animation::SWIPE, ANIMATION_SPEED);
            time = 0;
            phase = 0;
        }
    }
}

void ReadyState::EndState()
{

}

void ReadyState::SwitchOne()
{

}

void ReadyState::SwitchTwo()
{
    
}