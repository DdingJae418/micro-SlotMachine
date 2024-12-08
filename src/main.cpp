#include <fixed_rate_updater.h>
#include <game_manager.h>
#include <fnd_controller.h>
#include <buzzer_controller.h>
#include <switch_controller.h>
#include <game_states/game_states.h>
#include <fnd_animations.h>

int main(void)
{
    // Create modules
    FixedRateUpdater* updater = FixedRateUpdater::GetInstance();
    GameManager gameManager;
    FNDController* fndController = FNDController::GetInstance();
    BuzzerController* buzzerController = BuzzerController::GetInstance();

    // Add game states
    gameManager.AddGameState(State::READY, new ReadyState(&gameManager, fndController, buzzerController));

    // Add animations
    fndController->AddAnimation(Animation::NONE, new NoAnimation());
    fndController->AddAnimation(Animation::SWIPE, new SwipeAnimation());

    // Add update listeners
    updater->AddListener(fndController);
    updater->AddListener(buzzerController);
    updater->AddListener(&gameManager);

    // Mute buzzer when testing at the cafe
    //buzzerController->MuteBuzzer(true);

    // Start game with ready state
    gameManager.SetGameState(State::READY);

    // Update modules every frame
    while(true) updater->CallListeners();

    // Delete modules
    delete updater;
    delete fndController;
    delete buzzerController;

    return 0;
}