#include <game_manager.h>

GameManager& GameManager::GetInstance()
{
    static GameManager instance;
    return instance;
}

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

void GameManager::SwitchClick(Switch sw)
{
    if(currentState)
        sw == Switch::ONE ? currentState->SwitchOne() : currentState->SwitchTwo();
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