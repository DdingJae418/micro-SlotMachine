#ifndef READY_STATE_H
#define READY_STATE_H

#include "game_manager.h"

class ReadyState : public GameState
{
private:
    GameManager* gameManager;
public:
    ReadyState(GameManager* gm) : gameManager(gm) { }
    virtual void StartState();
    virtual void UpdateState();
    virtual void EndState();
};

#endif