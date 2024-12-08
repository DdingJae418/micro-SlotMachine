#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "game_manager.h"

class ReadyState : public GameState
{
private:
    GameManager* gameManager;
    FNDController* fnd;
    BuzzerController* buzzer;
    float time;
    int phase;
public:
    ReadyState(GameManager* gm, FNDController* fnd, BuzzerController* buzzer);
    void StartState() override;
    void UpdateState() override;
    void EndState() override;
};

#endif