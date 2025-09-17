#include <fnd_controller.h>
#include <buzzer_controller.h>
#include <game_enums.h>
#include "game_states.h"

constexpr float AnimationSpeed = 30;
constexpr float WaitingTime = 0.9;


ReadyState::ReadyState(GameManager& gm, FNDController& fnd, BuzzerController& buzzer)
    : GameState(gm, fnd, buzzer)
{ }

void ReadyState::StartState()
{
    // Set variables
    time = 0;
    phase = 0;

    // Empty FND display
    GetFndController().SetDisplay(Letter::None, false);
    GetFndController().StartAnimation(Animation::Plain);

    // Play ready sound
    GetBuzzerController().StartSound(&sounds::ReadySong, 2.2, true);
}

void ReadyState::UpdateState()
{
    if (GetFndController().IsAnimationPlaying()) return;
    
    if (phase == 0)
    {
        // Set 'PLAY' letter and start 'SWIPE' animation at the FND display
        GetFndController().SetDisplay(Letter::Play);
        GetFndController().StartAnimation(Animation::Swipe, AnimationSpeed);
        phase++;
    }
    else
    {
        // Count second
        time += Time::DeltaTime();

        // Swipe out 'PLAY' letter
        if(time > WaitingTime)
        {
            GetFndController().SetDisplay(Letter::None);
            GetFndController().StartAnimation(Animation::Swipe, AnimationSpeed);
            time = 0;
            phase = 0;
        }
    }
}

void ReadyState::SwitchOne()
{
    // Change to opening state
    GetGameManager().SetGameState(State::Opening);
}

void ReadyState::EndState() { }
void ReadyState::SwitchTwo() { }