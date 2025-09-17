#ifndef GAME_STATES_H
#define GAME_STATES_H

#include "game_manager.h"


class ReadyState : public GameState
{
private:
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
    float time;
    int phase;
private:
    void HandleFirstPhase();
    void HandleSecondPhase();
public:
    ResettingState(GameManager& gm, FNDController& fnd, BuzzerController& buzzer);
    void StartState() override;
    void UpdateState() override;
    void EndState() override;
    void SwitchOne() override;
    void SwitchTwo() override;
};

class StoppingState : public GameState
{
private:
    float delay;
    float time;
    int phase;
private:
    void HandleFirstPhase();
    void HandleSecondPhase();
    void HandleThirdPhase();
public:
    StoppingState(GameManager& gm, FNDController& fnd, BuzzerController& buzzer);
    void StartState() override;
    void UpdateState() override;
    void EndState() override;
    void SwitchOne() override;
    void SwitchTwo() override;
};

class ResultState : public GameState
{
private:
    Letter result;
    int phase;
    bool isAnimationOver;
private:
    void HandleFirstPhase();
    void HandleSecondPhase();
    void HandleThirdPhase();
public:
    ResultState(GameManager& gm, FNDController& fnd, BuzzerController& buzzer);
    void StartState() override;
    void UpdateState() override;
    void EndState() override;
    void SwitchOne() override;
    void SwitchTwo() override;
};

#endif