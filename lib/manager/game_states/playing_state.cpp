#include <fnd_controller.h>
#include <buzzer_controller.h>
#include <game_enums.h>
#include "game_states.h"


PlayingState::PlayingState(GameManager& gm, FNDController& fnd, BuzzerController& buzzer)
    : gm(gm), fnd(fnd), buzzer(buzzer)
{ }

void PlayingState::StartState()
{
    // Start playing song
    buzzer.StartSound(&sounds::PlayingSong, 5, true);
}

void PlayingState::UpdateState()
{   
    for (int i = stoppingReel; i < 4; i++)
        reelTime[i] += Time::DeltaTime();

    bool reelChanged = false;

    // Increase reel numbers
    for (int i = 0; i < 4; i++)
    {
        if (reelTime[i] > ReelDelay[i])
        {
            reelTime[i] = 0;
            reels[i] = (reels[i] + 1) % 10;
            reelChanged = true;
        }
    }

    // Show reel numbers
    if(reelChanged)
    {
        int num = reels[0] * 1000 + reels[1] * 100 + reels[2] * 10 + reels[3];
        fnd.SetDisplay(num);
        fnd.StartAnimation(Animation::Plain);
    }
}

void PlayingState::SwitchOne() 
{ 
    // Stop reel
    gm.SetGameState(State::Stopping);
}

void PlayingState::SwitchTwo() 
{ 
    // Reset game
    gm.SetGameState(State::Resetting);
}

void PlayingState::EndState() { }