#include <fixed_rate_updater.h>
#include <game_manager.h>
#include <fnd_controller.h>
#include <buzzer_controller.h>
#include <switch_controller.h>
#include <game_states/game_states.h>

int main(void)
{
    // Create modules
    FixedRateUpdater* updater = FixedRateUpdater::GetInstance();
    GameManager gameManager;
    FNDController* fndController = FNDController::GetInstance();
    BuzzerController buzzerController;
    SwitchController switchController;

    // Add game states
    gameManager.AddGameState(State::Ready, new ReadyState(&gameManager));

    // Add update listeners
    updater->AddListener(fndController);
    updater->AddListener(&buzzerController);
    updater->AddListener(&gameManager);

    // Start game with ready state
    gameManager.SetGameState(State::Ready);

    // Update modules every frame
    while(true) updater->CallListeners();

    // Delete modules
    delete updater;
    delete fndController;

    return 0;
}