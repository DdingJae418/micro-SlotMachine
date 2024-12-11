#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "game_manager.h"

class ReadyState : public GameState
{
private:
    GameManager& gm;
    FNDController& fnd;
    BuzzerController& buzzer;
    float time;
    int phase;
public:
    ReadyState(GameManager& gm, FNDController& fnd, BuzzerController& buzzer);
    void StartState() override;
    void UpdateState() override;
    void EndState() override;
    void SwitchOne() override;
    void SwitchTwo() override;
};

class OpeningState : public GameState
{
private:
    GameManager& gm;
    FNDController& fnd;
    BuzzerController& buzzer;
    float time;
    int phase;
    int availableReel;
    int recentReel;
private:
    void HandleFirstPhase();
    void HandleSecondPhase();
    void HandleThirdPhase();
    void HandleFourthPhase();
public:
    OpeningState(GameManager& gm, FNDController& fnd, BuzzerController& buzzer);
    void StartState() override;
    void UpdateState() override;
    void EndState() override;
    void SwitchOne() override;
    void SwitchTwo() override;
};

class PlayingState : public GameState
{
private:
    GameManager& gm;
    FNDController& fnd;
    BuzzerController& buzzer;
    float time;
    int phase;
public:
    PlayingState(GameManager& gm, FNDController& fnd, BuzzerController& buzzer);
    void StartState() override;
    void UpdateState() override;
    void EndState() override;
    void SwitchOne() override;
    void SwitchTwo() override;
};

class ResettingState : public GameState
{
private:
    GameManager& gm;
    FNDController& fnd;
    BuzzerController& buzzer;
    float time;
    int phase;
public:
    ResettingState(GameManager& gm, FNDController& fnd, BuzzerController& buzzer);
    void StartState() override;
    void UpdateState() override;
    void EndState() override;
    void SwitchOne() override;
    void SwitchTwo() override;
};

#endif