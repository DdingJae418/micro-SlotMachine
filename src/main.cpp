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
    GameManager::GetInstance().SetGameState(State::READY);

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

    gm.AddGameState(State::READY, new ReadyState(gm, fnd, buzzer));
    gm.AddGameState(State::OPENING, new OpeningState(gm, fnd, buzzer));
    gm.AddGameState(State::PLAYING, new PlayingState(gm, fnd, buzzer));
    gm.AddGameState(State::RESETTING, new ResettingState(gm, fnd, buzzer));
    gm.AddGameState(State::STOPPING, new StoppingState(gm, fnd, buzzer));
    gm.AddGameState(State::RESULT, new ResultState(gm, fnd, buzzer));
}

void AddAnimations()
{
    FNDController& fnd = FNDController::GetInstance();

    fnd.AddAnimation(Animation::NONE, new NoAnimation());
    fnd.AddAnimation(Animation::SWIPE, new SwipeAnimation());
    fnd.AddAnimation(Animation::FLICKER, new FlickerAnimation());
    fnd.AddAnimation(Animation::ROUND_ROBIN, new RoundRobinAnimation());
    fnd.AddAnimation(Animation::WRITE_FAIL, new WriteFailAnimation());
    fnd.AddAnimation(Animation::WRITE_1ST, new Write1stAnimation());
    fnd.AddAnimation(Animation::WRITE_2ND, new Write2ndAnimation());
    fnd.AddAnimation(Animation::WRITE_3RD, new Write3rdAnimation());
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