#include <game_manager.h>

void GameManager::AddGameState(State state, GameStatePtr statePtr)
{   
    gameStateMap[state] = statePtr;
}

void GameManager::RunGame(State state)
{
    // Set Starting state
    currentState = gameStateMap[state];

    // Start current State
    currentState->StartState();
}

GameManager::~GameManager()
{
    for (auto state : gameStateMap)
        delete state.second;
}