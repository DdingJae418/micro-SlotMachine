#include <fnd_controller.h>
#include <buzzer_controller.h>
#include <game_enums.h>
#include "game_states.h"

constexpr int FIRST_PHASE = 0;
constexpr int SECOND_PHASE = 1;
constexpr int THIRD_PHASE = 2;
constexpr int FOURTH_PHASE = 3;

constexpr float WAITING_TIME = 2;
constexpr float FIRST_ANIMATION_SPEED = 8;
constexpr float SECOND_ANIMATION_SPEED = 4;
constexpr float START_SOUND_SPEED = 5;
constexpr float START_PLAYING_SOUND_SPEED = 6;
constexpr float REEL_SOUND_SPEED = 10;


OpeningState::OpeningState(GameManager& gm, FNDController& fnd, BuzzerController& buzzer)
    : gm(gm), fnd(fnd), buzzer(buzzer)
{ }

void OpeningState::StartState()
{
    // Set variables
    time = 0;
    phase = FIRST_PHASE;
    availableReel = 0;
    recentReel = 0;

    // Flicker FND display
    fnd.SetDisplay(Letter::Play);
    fnd.StartAnimation(Animation::Flicker, FIRST_ANIMATION_SPEED);

    // Play start sound
    buzzer.StartSound(&sounds::START_SOUND, START_SOUND_SPEED);
}

void OpeningState::UpdateState()
{   
    switch(phase)
    {
    case FIRST_PHASE:
        HandleFirstPhase();
        break;
    case SECOND_PHASE:
        HandleSecondPhase();
        break;
    case THIRD_PHASE:
        HandleThirdPhase();
        break;
    case FOURTH_PHASE:
        HandleFourthPhase();
        break;
    default:
        break;
    }
}

// Wait a second
void OpeningState::HandleFirstPhase()
{
    if (fnd.IsAnimationPlaying()) return;

    time += Time::DeltaTime();
    if(time > 1)
    {
        time = 0;
        phase++;
    }
}

// Turn FND screen off
void OpeningState::HandleSecondPhase()
{
    fnd.SetDisplay(Letter::None);
    fnd.StartAnimation(Animation::Plain);
    phase++;
}


// Gradually show reels at the fnd
void OpeningState::HandleThirdPhase()
{
    for (int i = 0; i <= availableReel; i++)
        reelTime[i] += Time::DeltaTime();
    time += Time::DeltaTime();

    if (time > WAITING_TIME)
    {
        time = 0;
        if(availableReel < 3)
            availableReel++;
        else
        {
            fnd.StartAnimation(Animation::Flicker, SECOND_ANIMATION_SPEED);
            buzzer.StartSound(&sounds::START_PLAYING_SOUND, START_PLAYING_SOUND_SPEED);
            phase++;
            return;
        }
    }

    int changedReel = -1;

    // Increase reel numbers
    for (int i = 0; i < 4; i++)
    {
        if (reelTime[i] > REEL_DELAY[i])
        {
            reelTime[i] = 0;
            reels[i] = (reels[i] + 1) % 10;
            changedReel = i;
            if (i == availableReel) recentReel = i;
        }
    }

    // Show reel numbers and play reel sound
    if(changedReel > -1)
    {
        int num = reels[0] * 1000 + reels[1] * 100 + reels[2] * 10 + reels[3];
        fnd.SetDisplay(num);
        fnd.StartAnimation(Animation::Plain, 1, 0, recentReel);
        if (changedReel == recentReel) buzzer.StartSound(&sounds::REEL_SOUND, REEL_SOUND_SPEED);
    }
}

// After flickering animation, change to playing state
void OpeningState::HandleFourthPhase()
{
    if (!fnd.IsAnimationPlaying())
        gm.SetGameState(State::PLAYING);

    // Rotate reels while playing flickering animation
    for (int i = 0; i < 4; i++)
        reelTime[i] += Time::DeltaTime();

    bool reelChanged = false;

    // Increase reel numbers
    for (int i = 0; i < 4; i++)
    {
        if (reelTime[i] > REEL_DELAY[i])
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
    }
}


void OpeningState::SwitchOne() { }
void OpeningState::EndState() { }
void OpeningState::SwitchTwo() { }