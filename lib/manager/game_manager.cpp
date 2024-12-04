#include <game_manager.h>

void GameManager::AddGameState(State state, GameStatePtr statePtr)
{   
    gameStateMap[state] = statePtr;
}

void GameManager::SetGameState(State state)
{
    if(currentState) currentState->EndState();
    currentState = gameStateMap[state];
    currentState->StartState();
}

void GameManager::Update()
{
    if (currentState)
        currentState->UpdateState();
}

GameManager::~GameManager()
{
    for (auto state : gameStateMap)
        delete state.second;
}