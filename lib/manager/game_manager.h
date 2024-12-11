#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <map>
#include <fixed_rate_updater.h>
#include <game_enums.h>

using game_enums::State;
using game_enums::Switch;

class GameState;
typedef GameState* GameStatePtr;

class GameManager : public UpdateListener
{
private:
    static GameManager* instance;
    std::map<State, GameStatePtr> gameStateMap;
    GameState* currentState;
private:
    GameManager() : currentState(nullptr) {}
    ~GameManager();
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;
public:
    static GameManager& GetInstance();
    static void DestroyInstance();
    void AddGameState(State state, GameStatePtr statePtr);
    void SetGameState(State state);
    void SwitchClick(Switch sw);
    void Update() override;
};

class GameState
{
public:
    virtual void StartState() = 0;
    virtual void UpdateState() = 0;
    virtual void EndState() = 0;
    virtual void SwitchOne() = 0;
    virtual void SwitchTwo() = 0;
    virtual ~GameState() {};
};

class ReelManager {
public:
    static const float REEL_DELAY[4];
    static float reelTime[4];
    static int reels[4];
    static int stoppedReel;
};


#endif