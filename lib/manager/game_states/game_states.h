#ifndef GAME_STATES_H
#define GAME_STATES_H

#include "game_manager.h"


class ReadyState : public GameState
{
public:
    ReadyState(GameManager& gm, FNDController& fnd, BuzzerController& buzzer);
    void StartState() override;
    void UpdateState() override;
    void EndState() override;
    void SwitchOne() override;
    void SwitchTwo() override;

private:
    float time;
    int phase;
};

class OpeningState : public GameState
{
public:
    OpeningState(GameManager& gm, FNDController& fnd, BuzzerController& buzzer);
    void StartState() override;
    void UpdateState() override;
    void EndState() override;
    void SwitchOne() override;
    void SwitchTwo() override;

private:
    void HandleFirstPhase();
    void HandleSecondPhase();
    void HandleThirdPhase();
    void HandleFourthPhase();

    float time;
    int phase;
    int availableReel;
    int recentReel;
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
public:
    ResettingState(GameManager& gm, FNDController& fnd, BuzzerController& buzzer);
    void StartState() override;
    void UpdateState() override;
    void EndState() override;
    void SwitchOne() override;
    void SwitchTwo() override;

private:
    void HandleFirstPhase();
    void HandleSecondPhase();

    float time;
    int phase;
};

class StoppingState : public GameState
{
public:
    StoppingState(GameManager& gm, FNDController& fnd, BuzzerController& buzzer);
    void StartState() override;
    void UpdateState() override;
    void EndState() override;
    void SwitchOne() override;
    void SwitchTwo() override;

private:
    void HandleFirstPhase();
    void HandleSecondPhase();
    void HandleThirdPhase();

    float delay;
    float time;
    int phase;
};

class ResultState : public GameState
{
public:
    ResultState(GameManager& gm, FNDController& fnd, BuzzerController& buzzer);
    void StartState() override;
    void UpdateState() override;
    void EndState() override;
    void SwitchOne() override;
    void SwitchTwo() override;

private:
    void HandleFirstPhase();
    void HandleSecondPhase();
    void HandleThirdPhase();

    Letter result;
    int phase;
    bool isAnimationOver;
};

#endif