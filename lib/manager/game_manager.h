#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <map>
#include <fixed_rate_updater.h>
#include <game_enums.h>

using game_enums::State;
using game_enums::Switch;
using std::vector;

using GameStatePtr = class GameState*;

class FNDController;
class BuzzerController;

class GameManager : public UpdateListener
{
public:
    static GameManager& GetInstance();
    static void DestroyInstance();

    void AddGameState(State state, GameStatePtr statePtr);
    void SetGameState(State state);
    void SwitchClick(Switch sw);
    
    float GetReelDelay(int index) const { return ReelDelay[index]; }
    int GetStoppingReel() const { return stoppingReel; }
    void SetStoppingReel(int value) { stoppingReel = value; }

    vector<float>& GetReelTime() { return reelTime; }
    const vector<float>& GetReelTime() const { return reelTime; }
    vector<unsigned char>& GetReels() { return reels; }
    const vector<unsigned char>& GetReels() const { return reels; }

    virtual void Update() override;

private:    
    GameManager();
    ~GameManager();
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;  

    static GameManager* instance;
    std::map<State, GameStatePtr> gameStateMap;
    vector<float> reelTime;
    vector<unsigned char> reels;
    GameStatePtr currentState;
    const float ReelDelay[4];
    int stoppingReel;
    
};

class GameState
{
private:
    GameManager& gm;
    FNDController& fnd;
    BuzzerController& buzzer;

protected:
    GameManager& GetGameManager() { return gm; }
    const GameManager& GetGameManager() const { return gm; }
    FNDController& GetFndController() { return fnd; }
    const FNDController& GetFndController() const { return fnd; }
    BuzzerController& GetBuzzerController() { return buzzer; }
    const BuzzerController& GetBuzzerController() const { return buzzer; }

public:
    GameState(GameManager& gameManager, FNDController& fndController, BuzzerController& buzzerController)
        : gm(gameManager), fnd(fndController), buzzer(buzzerController) {}

    virtual void StartState() = 0;
    virtual void UpdateState() = 0;
    virtual void EndState() = 0;
    virtual void SwitchOne() = 0;
    virtual void SwitchTwo() = 0;
    virtual ~GameState() = default;
};


#endif