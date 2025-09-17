#include <fnd_controller.h>
#include <buzzer_controller.h>
#include <game_enums.h>
#include <algorithm>
#include "game_states.h"

constexpr int FirstPhase = 1;
constexpr int SecondPhase = 2;
constexpr int ThirdPhase = 3;

constexpr float FailSoundSpeed = 0.8;
constexpr float SuccessSoundSpeed = 2.5;
constexpr float SwipeSpeed = 10;
constexpr float RoundRobinSpeed = 15;
constexpr float WriteSpeed = 10;

Letter CheckResult();


ResultState::ResultState(GameManager& gm, FNDController& fnd, BuzzerController& buzzer)
    : gm(gm), fnd(fnd), buzzer(buzzer)
{ }

void ResultState::StartState()
{
    // // test
    // reels[0] = 0;
    // reels[1] = 2;
    // reels[2] = 1;
    // reels[3] = 3;
    // fnd.SetDisplay(0213);
    // fnd.StartAnimation(Animation::PLAIN);

    result = CheckResult();
    phase = FirstPhase;
    isAnimationOver = false;
}

void ResultState::UpdateState()
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

// Play fail/success sound and animation
void ResultState::HandleFirstPhase()
{
    if (result == Letter::Fail)
    {
        buzzer.StartSound(&sounds::FailSound, FailSoundSpeed);
        fnd.SetDisplay(Letter::None);
        fnd.StartAnimation(Animation::Swipe, SwipeSpeed);
    }
    else
    {
        buzzer.StartSound(&sounds::SuccessSound, SuccessSoundSpeed);
        fnd.StartAnimation(Animation::RoundRobin, RoundRobinSpeed);
    }
    phase++;
}

// Play writing animation according to the result
void ResultState::HandleSecondPhase()
{
    if (fnd.IsAnimationPlaying()) return;

    // Start writing animation
    fnd.SetDisplay(result);
    switch (result)
    {
    case Letter::Fail:
        fnd.SetDisplay(Letter::Fail);
        fnd.StartAnimation(Animation::WriteFail, WriteSpeed);
        break;
    case Letter::_1st:
        fnd.SetDisplay(Letter::_1st);
        fnd.StartAnimation(Animation::Write1st, WriteSpeed);
        break;
    case Letter::_2nd:
        fnd.SetDisplay(Letter::_2nd);
        fnd.StartAnimation(Animation::Write2nd, WriteSpeed);
        break;
    case Letter::_3rd:
        fnd.SetDisplay(Letter::_3rd);
        fnd.StartAnimation(Animation::Write3rd, WriteSpeed);
        break;;
    default:
        break;
    }

    phase++;
}

// Enable reset button
void ResultState::HandleThirdPhase()
{
    if (fnd.IsAnimationPlaying()) return;

    isAnimationOver = true;
}

void ResultState::SwitchTwo() 
{ 
    // Reset game after animation
    if (isAnimationOver)
        gm.SetGameState(State::Resetting);
}

Letter CheckResult()
{
    vector<unsigned char> results(reels);
    std::sort(results.begin(), results.end());

    int maxSameCnt = 1, currentSameCnt = 1;
    int maxContCnt = 1, currentContCnt = 1;

    for (size_t i = 1; i < results.size(); i++)
    {
        // Check for identical consecutive values
        if (results[i] == results[i - 1])
        {
            currentSameCnt++;
            maxSameCnt = std::max(maxSameCnt, currentSameCnt);
        }
        else
        {
            currentSameCnt = 1;
        }

        // Check for consecutive increasing values
        if (results[i] - results[i - 1] == 1)
        {
            currentContCnt++;
            maxContCnt = std::max(maxContCnt, currentContCnt);
        }
        else
        {
            currentContCnt = 1;
        }
    }

    // Return the result based on the counts
    if (maxSameCnt >= 4)
        return Letter::_1st;
    else if (maxContCnt >= 4)
        return Letter::_2nd;
    else if (maxSameCnt == 3 || maxContCnt == 3)
        return Letter::_3rd;
    else
        return Letter::Fail;
}



void ResultState::SwitchOne() { }
void ResultState::EndState() { }