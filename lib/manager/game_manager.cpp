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

GameManager* GameManager::instance = nullptr;

const float ReelManager::REEL_DELAY[4] = {0.6, 0.4, 0.3, 0.2};
float ReelManager::reelTime[4] = {0,0,0,0};
int ReelManager::reels[4] = {0,0,0,0};
int ReelManager::stoppedReel = -1;