#include <fnd_controller.h>
#include <buzzer_controller.h>
#include <game_enums.h>
#include "game_states.h"


PlayingState::PlayingState(GameManager& gm, FNDController& fnd, BuzzerController& buzzer)
    : gm(gm), fnd(fnd), buzzer(buzzer)
{ }

void PlayingState::StartState()
{
    // Set variables
    time = 0;
    phase = 0;
}

void PlayingState::UpdateState()
{   
    for (int i = ReelManager::stoppedReel + 1; i < 4; i++)
        ReelManager::reelTime[i] += Time::DeltaTime();

    bool reelChanged = false;

    // Increase reel numbers
    for (int i = 0; i < 4; i++)
    {
        if (ReelManager::reelTime[i] > ReelManager::REEL_DELAY[i])
        {
            ReelManager::reelTime[i] = 0;
            ReelManager::reels[i] = (ReelManager::reels[i] + 1) % 10;
            reelChanged = true;
        }
    }

    // Show reel numbers
    if(reelChanged)
    {
        int num = ReelManager::reels[0] * 1000 + ReelManager::reels[1] * 100 + 
            ReelManager::reels[2] * 10 + ReelManager::reels[3];
        fnd.SetDisplay(num);
        fnd.StartAnimation(Animation::NONE);
    }
}


void PlayingState::SwitchOne() { }
void PlayingState::EndState() { }
void PlayingState::SwitchTwo() { }