#include <fnd_controller.h>
#include <buzzer_controller.h>
#include <game_enums.h>
#include <algorithm>
#include "game_states.h"

constexpr int FIRST_PHASE = 1;
constexpr int SECOND_PHASE = 2;
constexpr int THIRD_PHASE = 3;

constexpr float FAIL_SOUND_SPEED = 0.8;
constexpr float SUCCESS_SOUND_SPEED = 2.5;
constexpr float SwipeSpeed = 10;
constexpr float ROUND_ROBIN_SPEED = 15;
constexpr float WRITE_SPEED = 10;

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
    phase = FIRST_PHASE;
    isAnimationOver = false;
}

void ResultState::UpdateState()
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

// Play fail/success sound and animation
void ResultState::HandleFirstPhase()
{
    if (result == Letter::Fail)
    {
        buzzer.StartSound(&sounds::FAIL_SOUND, FAIL_SOUND_SPEED);
        fnd.SetDisplay(Letter::None);
        fnd.StartAnimation(Animation::Swipe, SwipeSpeed);
    }
    else
    {
        buzzer.StartSound(&sounds::SUCCESS_SOUND, SUCCESS_SOUND_SPEED);
        fnd.StartAnimation(Animation::RoundRobin, ROUND_ROBIN_SPEED);
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
        fnd.StartAnimation(Animation::WriteFail, WRITE_SPEED);
        break;
    case Letter::_1st:
        fnd.SetDisplay(Letter::_1st);
        fnd.StartAnimation(Animation::Write1st, WRITE_SPEED);
        break;
    case Letter::_2nd:
        fnd.SetDisplay(Letter::_2nd);
        fnd.StartAnimation(Animation::Write2nd, WRITE_SPEED);
        break;
    case Letter::_3rd:
        fnd.SetDisplay(Letter::_3rd);
        fnd.StartAnimation(Animation::Write3rd, WRITE_SPEED);
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
        gm.SetGameState(State::RESETTING);
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