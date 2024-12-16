#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "game_manager.h"

// Reel variables
inline const float REEL_DELAY[4] = {0.6, 0.4, 0.3, 0.2};
inline vector<float> reelTime = {0,0,0,0};
inline vector<unsigned char> reels = {0,0,0,0};
inline int stoppingReel = 0;


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
    GameManager& gm;
    FNDController& fnd;
    BuzzerController& buzzer;
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
    GameManager& gm;
    FNDController& fnd;
    BuzzerController& buzzer;
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