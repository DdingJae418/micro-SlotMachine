#include <fnd_controller.h>
#include <buzzer_controller.h>
#include <game_enums.h>
#include "game_states.h"

constexpr int FirstPhase = 0;
constexpr int SecondPhase = 1;
constexpr int ThirdPhase = 2;
constexpr int FourthPhase = 3;

constexpr float WaitingTime = 2;
constexpr float FirstAnimationSpeed = 8;
constexpr float SecondAnimationSpeed = 4;
constexpr float StartSoundSpeed = 5;
constexpr float StartPlayingSoundSpeed = 6;
constexpr float ReelSoundSpeed = 10;


OpeningState::OpeningState(GameManager& gm, FNDController& fnd, BuzzerController& buzzer)
    : gm(gm), fnd(fnd), buzzer(buzzer)
{ }

void OpeningState::StartState()
{
    // Set variables
    time = 0;
    phase = FirstPhase;
    availableReel = 0;
    recentReel = 0;

    // Flicker FND display
    fnd.SetDisplay(Letter::Play);
    fnd.StartAnimation(Animation::Flicker, FirstAnimationSpeed);

    // Play start sound
    buzzer.StartSound(&sounds::StartSound, StartSoundSpeed);
}

void OpeningState::UpdateState()
{   
    switch(phase)
    {
    case FirstPhase:
        HandleFirstPhase();
        break;
    case SecondPhase:
        HandleSecondPhase();
        break;
    case ThirdPhase:
        HandleThirdPhase();
        break;
    case FourthPhase:
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
    auto& reelTime = gm.GetReelTime();
    for (int i = 0; i <= availableReel; i++)
        reelTime[i] += Time::DeltaTime();
    time += Time::DeltaTime();

    if (time > WaitingTime)
    {
        time = 0;
        if(availableReel < 3)
            availableReel++;
        else
        {
            fnd.StartAnimation(Animation::Flicker, SecondAnimationSpeed);
            buzzer.StartSound(&sounds::StartPlayingSound, StartPlayingSoundSpeed);
            phase++;
            return;
        }
    }

    int changedReel = -1;

    // Increase reel numbers
    auto& reels = gm.GetReels();
    for (int i = 0; i < 4; i++)
    {
        if (reelTime[i] > gm.GetReelDelay(i))
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
        if (changedReel == recentReel) buzzer.StartSound(&sounds::ReelSound, ReelSoundSpeed);
    }
}

// After flickering animation, change to playing state
void OpeningState::HandleFourthPhase()
{
    if (!fnd.IsAnimationPlaying())
        gm.SetGameState(State::Playing);

    // Rotate reels while playing flickering animation
    auto& reelTime = gm.GetReelTime();
    auto& reels = gm.GetReels();
    for (int i = 0; i < 4; i++)
        reelTime[i] += Time::DeltaTime();

    bool reelChanged = false;

    // Increase reel numbers
    for (int i = 0; i < 4; i++)
    {
        if (reelTime[i] > gm.GetReelDelay(i))
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