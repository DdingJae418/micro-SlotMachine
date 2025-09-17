#include <fnd_controller.h>
#include <buzzer_controller.h>
#include <game_enums.h>
#include "game_states.h"

constexpr int FirstPhase = 1;
constexpr int SecondPhase = 2;
constexpr int ThirdPhase = 3;

constexpr float FlickerSpeed = 5;
constexpr float SwipeSpeed = 20;
constexpr float SoundSpeed = 5;
constexpr float WaitingTime = 1.5;


ResettingState::ResettingState(GameManager& gm, FNDController& fnd, BuzzerController& buzzer)
    : gm(gm), fnd(fnd), buzzer(buzzer)
{ }

void ResettingState::StartState()
{
    // Set variables
    time = 0;
    phase = FirstPhase;

    // Reset reels
    auto& reelTime = gm.GetReelTime();
    auto& reels = gm.GetReels();
    std::fill(reelTime.begin(), reelTime.end(), 0);
    std::fill(reels.begin(), reels.end(), 0);
    gm.SetStoppingReel(0);

    // Stop and flicker current screen
    fnd.StopAnimations();
    fnd.StartAnimation(Animation::Flicker, FlickerSpeed);

    // Play reset sound
    buzzer.StartSound(&sounds::ResetSound, SoundSpeed);
}

void ResettingState::UpdateState()
{   
    switch (phase)
    {
    case FirstPhase:
        HandleFirstPhase();
        break;
    case SecondPhase:
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

    fnd.SetDisplay(Letter::None);
    fnd.StartAnimation(Animation::Swipe, SwipeSpeed);
    phase++;
}

// Wait a little and change to ready state
void ResettingState::HandleSecondPhase()
{
    if(fnd.IsAnimationPlaying()) return;

    time += Time::DeltaTime();
    if (time > WaitingTime)
    {
        gm.SetGameState(State::Ready);
    }
}

void ResettingState::SwitchOne() { }
void ResettingState::EndState() { }
void ResettingState::SwitchTwo() { }