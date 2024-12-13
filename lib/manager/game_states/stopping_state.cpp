#include <fnd_controller.h>
#include <buzzer_controller.h>
#include <game_enums.h>
#include "game_states.h"

constexpr int FIRST_PHASE = 1;
constexpr int SECOND_PHASE = 2;
constexpr int THIRD_PHASE = 3;

constexpr float LEVER_SOUND_SPEED = 3;
constexpr float REEL_SOUND_SPEED = 10;
constexpr float SWIPE_SPEED = 20;
constexpr float FIRST_FLICKER_SPEED = 10;
constexpr float LAST_FLICKER_SPEED = 6;
constexpr float SLOW_FACTOR = 0.05;
constexpr float MAX_DELAY = 1;


StoppingState::StoppingState(GameManager& gm, FNDController& fnd, BuzzerController& buzzer)
    : gm(gm), fnd(fnd), buzzer(buzzer)
{ }

void StoppingState::StartState()
{
    // Set variables
    delay = 0;
    time = 0;
    phase = FIRST_PHASE;

    // Play lever sound
    buzzer.StartSound(&sounds::LEVER_SOUND, LEVER_SOUND_SPEED);

    // Swipe out right side of the stopping reel
    if (stoppingReel < 3)
    {
        fnd.SetDisplay(Letter::NONE);
        fnd.StartAnimation(Animation::SWIPE, SWIPE_SPEED, stoppingReel + 1);
    }

    // Flicker stopping reel at first
    fnd.StartAnimation(Animation::FLICKER, FIRST_FLICKER_SPEED, stoppingReel, stoppingReel);
}

void StoppingState::UpdateState()
{  
    switch (phase)
    {
    case FIRST_PHASE:
        HandleFirstPhase();
        break;
    case SECOND_PHASE:
        HandleSecondPhase();
        break;
    case THIRD_PHASE:
        HandleThirdPhase();
    default:
        break;
    }
}

// Slowly stop reel
void StoppingState::HandleFirstPhase()
{
    reelTime[stoppingReel] += Time::DeltaTime();
    time += Time::DeltaTime();

    // Increase stopping reel number, and slow down speed
    if (reelTime[stoppingReel] > REEL_DELAY[stoppingReel] + delay)
    {
        reelTime[stoppingReel] = 0;
        reels[stoppingReel] = (reels[stoppingReel] + 1) % 10;
        delay = SLOW_FACTOR * time * time;

        // Show stopped/stopping reel numbers
        int num = reels[0] * 1000 + reels[1] * 100 + reels[2] * 10 + reels[3];
        fnd.SetDisplay(num, true, 0, stoppingReel);

        if (delay < MAX_DELAY)
        {
            if(!fnd.IsAnimationPlaying())
                fnd.StartAnimation(Animation::NONE, 1, 0, stoppingReel);
            if(!buzzer.IsSoundPlaying())
                buzzer.StartSound(&sounds::REEL_SOUND, REEL_SOUND_SPEED);
        }
        else // Slowed down enough
        {
            fnd.StartAnimation(Animation::FLICKER, LAST_FLICKER_SPEED, stoppingReel, stoppingReel);
            buzzer.StartSound(&sounds::REEL_STOP_SOUND, LEVER_SOUND_SPEED);
            phase++;
        }
    }
}

// Show remaining reels or go to the result state
void StoppingState::HandleSecondPhase()
{
    if (fnd.IsAnimationPlaying()) return;

    if(stoppingReel < 3)
    {
        int num = reels[0] * 1000 + reels[1] * 100 + reels[2] * 10 + reels[3];
        fnd.SetDisplay(num, true, stoppingReel + 1);
        fnd.StartAnimation(Animation::SWIPE, SWIPE_SPEED, stoppingReel++);
        phase++;
    }
    else
    {
        gm.SetGameState(State::RESULT);
    }
}

// Resume playing
void StoppingState::HandleThirdPhase()
{
    if (fnd.IsAnimationPlaying()) return;

    gm.SetGameState(State::PLAYING);
}


void StoppingState::EndState() { }
void StoppingState::SwitchOne() { }
void StoppingState::SwitchTwo() { }