#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <map>
#include <fixed_rate_updater.h>
#include <game_enums.h>
using game_enums::State;

class GameState;
typedef GameState* GameStatePtr;

class GameManager : public UpdateListener
{
private:
    std::map<State, GameStatePtr> gameStateMap;
    GameStatePtr currentState;
public:
    GameManager() : currentState(nullptr) {}
    void AddGameState(State state, GameStatePtr statePtr);
    void SetGameState(State state);
    virtual void Update();
    ~GameManager();
};

class GameState
{
public:
    virtual void StartState() = 0;
    virtual void UpdateState() = 0;
    virtual void EndState() = 0;
    virtual ~GameState() {};
};


#endif