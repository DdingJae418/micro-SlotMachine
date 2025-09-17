#include <game_manager.h>

GameManager& GameManager::GetInstance()
{
    if (!instance) instance = new GameManager();
    return *instance;
}

void GameManager::DestroyInstance()
{
    delete instance;
    instance = nullptr;
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
        sw == Switch::One ? currentState->SwitchOne() : currentState->SwitchTwo();
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

GameManager* GameManager::instance = nullptr;