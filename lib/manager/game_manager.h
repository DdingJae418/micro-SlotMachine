#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <map>
#include <game_enums.h>

using game_enums::State;

class GameState;

typedef GameState* GameStatePtr;


class GameManager
{
private:
    std::map<State, GameStatePtr> gameStateMap;
    GameStatePtr currentState;
public:
    void AddGameState(State state, GameStatePtr statePtr);
    void RunGame(State state);
    ~GameManager();
};

class GameState
{
public:
    virtual void StartState() = 0;
    virtual void UpdateState() = 0;
    virtual void EndState() = 0;
};


#endif