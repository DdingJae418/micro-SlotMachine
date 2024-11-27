#include <game_manager.h>
#include <fnd_controller.h>
#include <game_states.h>
#include <avr/interrupt.h>

int main(void)
{
    // Create modules
    GameManager gameManager;
    FNDController fnd;

    // Add game states
    gameManager.AddGameState(State::Ready, new ReadyState(gameManager));

    
    // Start game with ready state
    gameManager.RunGame(State::Ready);

    // while(1)
    // {

    // }

    return 0;
}