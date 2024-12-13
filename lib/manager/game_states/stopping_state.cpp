#include <fnd_controller.h>
#include <buzzer_controller.h>
#include <game_enums.h>
#include "game_states.h"

const float LEVER_SOUND_SPEED = 4;
const float SWIPE_SPEED = 20;


StoppingState::StoppingState(GameManager& gm, FNDController& fnd, BuzzerController& buzzer)
    : gm(gm), fnd(fnd), buzzer(buzzer), MAX_DELAY(3)
{ }

void StoppingState::StartState()
{
    // Set variables
    time = 0;
    phase = 0;

    // Play lever sound
    buzzer.StartSound(&sounds::LEVER_SOUND, LEVER_SOUND_SPEED);

    // Swipe out right side of the stopping reel
    if (stoppingReel < 3)
    {
        fnd.SetDisplay(Letter::NONE);
        fnd.StartAnimation(Animation::SWIPE, SWIPE_SPEED, stoppingReel + 1);
    }
}

void StoppingState::UpdateState()
{  
    reelTime[stoppingReel] += Time::DeltaTime();

    bool reelChanged = false;

    // Increase stopping reel number
    if (reelTime[stoppingReel] > REEL_DELAY[stoppingReel])
    {
        reelTime[stoppingReel] = 0;
        reels[stoppingReel] = (reels[stoppingReel] + 1) % 10;
        reelChanged = true;
    }


    // Show stopped/stopping reel numbers
    if(reelChanged)
    {
        int num = reels[0] * 1000 + reels[1] * 100 + reels[2] * 10 + reels[3];
        fnd.SetDisplay(num, true, 0, stoppingReel);
        fnd.StartAnimation(Animation::NONE, 1, 0, stoppingReel);
    }
}


void StoppingState::SwitchOne() { }
void StoppingState::EndState() { }
void StoppingState::SwitchTwo() { }