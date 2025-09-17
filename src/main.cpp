#include <fixed_rate_updater.h>
#include <game_manager.h>
#include <fnd_controller.h>
#include <buzzer_controller.h>
#include <switch_controller.h>
#include <game_states/game_states.h>
#include <fnd_animations.h>

void AddGameStates();
void AddAnimations();
void AddUpdateListeners();
void DestroySingleTones();

int main(void)
{   
    // Initial settings
    AddGameStates();
    AddAnimations();
    AddUpdateListeners();

    // Mute buzzer when testing
    //BuzzerController::GetInstance().MuteBuzzer(true);

    // Start game with ready state
    GameManager::GetInstance().SetGameState(State::Ready);

    // Update modules every frame
    FixedRateUpdater& updater = FixedRateUpdater::GetInstance();
    while(true) updater.CallListeners();

    // Destory all single tone objects
    DestroySingleTones();

    return 0;
}

void AddGameStates()
{
    GameManager& gm = GameManager::GetInstance();
    FNDController& fnd = FNDController::GetInstance();
    BuzzerController& buzzer = BuzzerController::GetInstance();

    gm.AddGameState(State::Ready, new ReadyState(gm, fnd, buzzer));
    gm.AddGameState(State::Opening, new OpeningState(gm, fnd, buzzer));
    gm.AddGameState(State::Playing, new PlayingState(gm, fnd, buzzer));
    gm.AddGameState(State::Resetting, new ResettingState(gm, fnd, buzzer));
    gm.AddGameState(State::Stopping, new StoppingState(gm, fnd, buzzer));
    gm.AddGameState(State::Result, new ResultState(gm, fnd, buzzer));
}

void AddAnimations()
{
    FNDController& fnd = FNDController::GetInstance();

    fnd.AddAnimation(Animation::Plain, new PlainAnimation());
    fnd.AddAnimation(Animation::Swipe, new SwipeAnimation());
    fnd.AddAnimation(Animation::Flicker, new FlickerAnimation());
    fnd.AddAnimation(Animation::RoundRobin, new RoundRobinAnimation());
    fnd.AddAnimation(Animation::WriteFail, new WriteFailAnimation());
    fnd.AddAnimation(Animation::Write1st, new Write1stAnimation());
    fnd.AddAnimation(Animation::Write2nd, new Write2ndAnimation());
    fnd.AddAnimation(Animation::Write3rd, new Write3rdAnimation());
}

void AddUpdateListeners()
{
    FixedRateUpdater& updater = FixedRateUpdater::GetInstance();

    updater.AddListener(&FNDController::GetInstance());
    updater.AddListener(&BuzzerController::GetInstance());
    updater.AddListener(&SwitchController::GetInstance());
    updater.AddListener(&GameManager::GetInstance());
}

void DestroySingleTones()
{
    FixedRateUpdater::DestroyInstance();
    SwitchController::DestroyInstance();
    GameManager::DestroyInstance();
    BuzzerController::DestroyInstance();
    FNDController::DestroyInstance();
}