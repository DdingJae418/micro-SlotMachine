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
    while(true) FixedRateUpdater::GetInstance().CallListeners();

    return 0;
}

void AddGameStates()
{
    GameManager& gm = GameManager::GetInstance();
    FNDController& fnd = FNDController::GetInstance();
    BuzzerController& buzzer = BuzzerController::GetInstance();

    gm.AddGameState(State::READY, new ReadyState(gm, fnd, buzzer));
}

void AddAnimations()
{
    FNDController& fnd = FNDController::GetInstance();

    fnd.AddAnimation(Animation::NONE, new NoAnimation());
    fnd.AddAnimation(Animation::SWIPE, new SwipeAnimation());
}

void AddUpdateListeners()
{
    FixedRateUpdater& updater = FixedRateUpdater::GetInstance();

    updater.AddListener(&FNDController::GetInstance());
    updater.AddListener(&BuzzerController::GetInstance());
    updater.AddListener(&SwitchController::GetInstance());
    updater.AddListener(&GameManager::GetInstance());
}