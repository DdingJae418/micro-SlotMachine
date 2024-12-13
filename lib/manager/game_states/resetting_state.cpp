#include <fnd_controller.h>
#include <buzzer_controller.h>
#include <game_enums.h>
#include "game_states.h"

constexpr int FIRST_PHASE = 1;
constexpr int SECOND_PHASE = 2;
constexpr int THIRD_PHASE = 3;

constexpr float FLICKER_SPEED = 5;
constexpr float SWIPE_SPEED = 20;
constexpr float SOUND_SPEED = 5;
constexpr float WAITING_TIME = 1.5;


ResettingState::ResettingState(GameManager& gm, FNDController& fnd, BuzzerController& buzzer)
    : gm(gm), fnd(fnd), buzzer(buzzer)
{ }

void ResettingState::StartState()
{
    // Set variables
    time = 0;
    phase = FIRST_PHASE;

    // Reset reels
    std::fill(reelTime.begin(), reelTime.end(), 0);
    std::fill(reels.begin(), reels.end(), 0);
    stoppingReel = 0;

    // Flicker current screen
    fnd.StartAnimation(Animation::FLICKER, FLICKER_SPEED);

    // Play reset sound
    buzzer.StartSound(&sounds::RESET_SOUND, SOUND_SPEED);
}

void ResettingState::UpdateState()
{   
    switch (phase)
    {
    case FIRST_PHASE:
        HandleFirstPhase();
        break;
    case SECOND_PHASE:
        HandleSecondPhase();
        break;
    default:
        break;
    }
}

// After flicker animation, play swipe animation
void ResettingState::HandleFirstPhase()
{
    if(fnd.IsAnimationPlaying()) return;

    fnd.SetDisplay(Letter::NONE);
    fnd.StartAnimation(Animation::SWIPE, SWIPE_SPEED);
    phase++;
}

// Wait a little and change to ready state
void ResettingState::HandleSecondPhase()
{
    if(fnd.IsAnimationPlaying()) return;

    time += Time::DeltaTime();
    if (time > WAITING_TIME)
    {
        gm.SetGameState(State::READY);
    }
}

void ResettingState::SwitchOne() { }
void ResettingState::EndState() { }
void ResettingState::SwitchTwo() { }