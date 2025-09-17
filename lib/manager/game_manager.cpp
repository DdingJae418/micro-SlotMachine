#include <game_manager.h>

GameManager::GameManager()
    : currentState {nullptr}
    , ReelDelay {0.6f, 0.4f, 0.3f, 0.2f}
    , reelTime(4, 0.0f)
    , reels(4, 0)
    , stoppingReel {0}
{
}

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