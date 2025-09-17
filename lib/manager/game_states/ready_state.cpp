#include <fnd_controller.h>
#include <buzzer_controller.h>
#include <game_enums.h>
#include "game_states.h"

constexpr float AnimationSpeed = 30;
constexpr float WaitingTime = 0.9;


ReadyState::ReadyState(GameManager& gm, FNDController& fnd, BuzzerController& buzzer)
    : gm(gm), fnd(fnd), buzzer(buzzer)
{ }

void ReadyState::StartState()
{
    // Set variables
    time = 0;
    phase = 0;

    // Empty FND display
    fnd.SetDisplay(Letter::None, false);
    fnd.StartAnimation(Animation::Plain);

    // Play ready sound
    buzzer.StartSound(&sounds::ReadySong, 2.2, true);
}

void ReadyState::UpdateState()
{
    if (fnd.IsAnimationPlaying()) return;
    
    if (phase == 0)
    {
        // Set 'PLAY' letter and start 'SWIPE' animation at the FND display
        fnd.SetDisplay(Letter::Play);
        fnd.StartAnimation(Animation::Swipe, AnimationSpeed);
        phase++;
    }
    else
    {
        // Count second
        time += Time::DeltaTime();

        // Swipe out 'PLAY' letter
        if(time > WaitingTime)
        {
            fnd.SetDisplay(Letter::None);
            fnd.StartAnimation(Animation::Swipe, AnimationSpeed);
            time = 0;
            phase = 0;
        }
    }
}

void ReadyState::SwitchOne()
{
    // Change to opening state
    gm.SetGameState(State::Opening);
}

void ReadyState::EndState() { }
void ReadyState::SwitchTwo() { }