#include <fnd_controller.h>
#include <buzzer_controller.h>
#include <game_enums.h>
#include "game_states.h"

constexpr int FirstPhase = 1;
constexpr int SecondPhase = 2;
constexpr int ThirdPhase = 3;

constexpr float LeverSoundSpeed = 3;
constexpr float ReelSoundSpeed = 10;
constexpr float SwipeSpeed = 20;
constexpr float FirstFlickerSpeed = 10;
constexpr float LastFlickerSpeed = 6;
constexpr float SlowFactor = 0.05;
constexpr float MaxDelay = 1;


StoppingState::StoppingState(GameManager& gm, FNDController& fnd, BuzzerController& buzzer)
    : gm(gm), fnd(fnd), buzzer(buzzer)
{ }

void StoppingState::StartState()
{
    // Set variables
    delay = 0;
    time = 0;
    phase = FirstPhase;

    // Play lever sound
    buzzer.StartSound(&sounds::LeverSound, LeverSoundSpeed);

    auto& reels = gm.GetReels();
    int stoppingReel = gm.GetStoppingReel();

    // Swipe out right side of the stopping reel
    if (stoppingReel < reels.size() - 1)
    {
        fnd.SetDisplay(Letter::None);
        fnd.StartAnimation(Animation::Swipe, SwipeSpeed, stoppingReel + 1);
    }

    // Flicker stopping reel at first
    int num = reels[0] * 1000 + reels[1] * 100 + reels[2] * 10 + reels[3];
    fnd.SetDisplay(num, true, stoppingReel, stoppingReel);
    fnd.StartAnimation(Animation::Flicker, FirstFlickerSpeed, stoppingReel, stoppingReel);
}

void StoppingState::UpdateState()
{  
    switch (phase)
    {
    case FirstPhase:
        HandleFirstPhase();
        break;
    case SecondPhase:
        HandleSecondPhase();
        break;
    case ThirdPhase:
        HandleThirdPhase();
    default:
        break;
    }
}

// Slowly stop reel
void StoppingState::HandleFirstPhase()
{
    auto& reelTime = gm.GetReelTime();
    auto& reels = gm.GetReels();
    int stoppingReel = gm.GetStoppingReel();

    reelTime[stoppingReel] += Time::DeltaTime();
    time += Time::DeltaTime();

    // Increase stopping reel number, and slow down speed
    if (reelTime[stoppingReel] > gm.GetReelDelay(stoppingReel) + delay)
    {
        reelTime[stoppingReel] = 0;
        reels[stoppingReel] = (reels[stoppingReel] + 1) % 10;
        delay = SlowFactor * time * time;

        // Show stopped/stopping reel numbers
        int num = reels[0] * 1000 + reels[1] * 100 + reels[2] * 10 + reels[3];
        fnd.SetDisplay(num, true, 0, stoppingReel);

        if (delay < MaxDelay)
        {
            if(!fnd.IsAnimationPlaying())
                fnd.StartAnimation(Animation::Plain, 1, 0, stoppingReel);
            if(!buzzer.IsSoundPlaying())
                buzzer.StartSound(&sounds::ReelSound, ReelSoundSpeed);
        }
        else // Slowed down enough
        {
            fnd.StartAnimation(Animation::Flicker, LastFlickerSpeed, stoppingReel, stoppingReel);
            buzzer.StartSound(&sounds::ReelStopSound, LeverSoundSpeed);
            phase++;
        }
    }
}

// Show remaining reels or go to the result state
void StoppingState::HandleSecondPhase()
{
    if (fnd.IsAnimationPlaying()) return;

    auto& reels = gm.GetReels();
    int stoppingReel = gm.GetStoppingReel();

    if(stoppingReel < 3)
    {
        int num = reels[0] * 1000 + reels[1] * 100 + reels[2] * 10 + reels[3];
        fnd.SetDisplay(num, true, stoppingReel + 1);
        fnd.StartAnimation(Animation::Swipe, SwipeSpeed, stoppingReel);
        gm.SetStoppingReel(stoppingReel + 1);
        phase++;
    }
    else
    {
        gm.SetGameState(State::Result);
    }
}

// Resume playing
void StoppingState::HandleThirdPhase()
{
    if (fnd.IsAnimationPlaying()) return;

    gm.SetGameState(State::Playing);
}

void StoppingState::EndState() { }
void StoppingState::SwitchOne() { }
void StoppingState::SwitchTwo() { }