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

Letter CheckResult(GameManager& gm);


ResultState::ResultState(GameManager& gm, FNDController& fnd, BuzzerController& buzzer)
    : GameState(gm, fnd, buzzer)
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

    result = CheckResult(GetGameManager());
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
        GetBuzzerController().StartSound(&sounds::FailSound, FailSoundSpeed);
        GetFndController().SetDisplay(Letter::None);
        GetFndController().StartAnimation(Animation::Swipe, SwipeSpeed);
    }
    else
    {
        GetBuzzerController().StartSound(&sounds::SuccessSound, SuccessSoundSpeed);
        GetFndController().StartAnimation(Animation::RoundRobin, RoundRobinSpeed);
    }
    phase++;
}

// Play writing animation according to the result
void ResultState::HandleSecondPhase()
{
    if (GetFndController().IsAnimationPlaying()) return;

    // Start writing animation
    GetFndController().SetDisplay(result);
    switch (result)
    {
    case Letter::Fail:
        GetFndController().SetDisplay(Letter::Fail);
        GetFndController().StartAnimation(Animation::WriteFail, WriteSpeed);
        break;
    case Letter::_1st:
        GetFndController().SetDisplay(Letter::_1st);
        GetFndController().StartAnimation(Animation::Write1st, WriteSpeed);
        break;
    case Letter::_2nd:
        GetFndController().SetDisplay(Letter::_2nd);
        GetFndController().StartAnimation(Animation::Write2nd, WriteSpeed);
        break;
    case Letter::_3rd:
        GetFndController().SetDisplay(Letter::_3rd);
        GetFndController().StartAnimation(Animation::Write3rd, WriteSpeed);
        break;;
    default:
        break;
    }

    phase++;
}

// Enable reset button
void ResultState::HandleThirdPhase()
{
    if (GetFndController().IsAnimationPlaying()) return;

    isAnimationOver = true;
}

void ResultState::SwitchTwo() 
{ 
    // Reset game after animation
    if (isAnimationOver)
        GetGameManager().SetGameState(State::Resetting);
}

Letter CheckResult(GameManager& gm)
{
    const auto& reels = gm.GetReels();
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