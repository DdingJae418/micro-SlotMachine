#include <fnd_controller.h>
#include <buzzer_controller.h>
#include <game_enums.h>
#include "game_states.h"

constexpr int FIRST_PHASE = 1;
constexpr int SECOND_PHASE = 2;

constexpr float FAIL_SOUND_SPEED = 0.8;
constexpr float SUCCESS_SOUND_SPEED = 2.5;
constexpr float SWIPE_SPEED = 2;
constexpr float ROUND_ROBIN_SPEED = 1;
constexpr float WRITE_SPEED = 1;

Letter CheckResult();


ResultState::ResultState(GameManager& gm, FNDController& fnd, BuzzerController& buzzer)
    : gm(gm), fnd(fnd), buzzer(buzzer)
{ }

void ResultState::StartState()
{
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
    default:
        break;
    }
}

// Play fail/success sound and animation
void ResultState::HandleFirstPhase()
{
    if (result == Letter::FAIL)
    {
        buzzer.StartSound(&sounds::FAIL_SOUND, FAIL_SOUND_SPEED);
        fnd.SetDisplay(Letter::NONE);
        fnd.StartAnimation(Animation::SWIPE, SWIPE_SPEED);
    }
    else
    {
        buzzer.StartSound(&sounds::SUCCESS_SOUND, SUCCESS_SOUND_SPEED);
        fnd.StartAnimation(Animation::ROUND_ROBIN, ROUND_ROBIN_SPEED);
    }
    phase++;
}

// Play writingR animation according to the result
void ResultState::HandleSecondPhase()
{
    if (fnd.IsAnimationPlaying()) return;

    fnd.SetDisplay(result);
    switch (result)
    {
    case Letter::FAIL:
        fnd.StartAnimation(Animation::WRITE_FAIL, WRITE_SPEED);
        break;
    case Letter::_1ST:
        fnd.StartAnimation(Animation::WRITE_1ST, WRITE_SPEED);
        break;
    case Letter::_2ND:
        fnd.StartAnimation(Animation::WRITE_2ND, WRITE_SPEED);
        break;
    case Letter::_3RD:
        fnd.StartAnimation(Animation::WRITE_3RD, WRITE_SPEED);
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
    return Letter::FAIL;
}



void ResultState::SwitchOne() { }
void ResultState::EndState() { }