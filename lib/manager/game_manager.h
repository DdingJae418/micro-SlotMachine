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
public:
    static GameManager& GetInstance();
    static void DestroyInstance();
    void AddGameState(State state, GameStatePtr statePtr);
    void SetGameState(State state);
    void SwitchClick(Switch sw);
    void Update() override;

    // Reel management methods
    float GetReelDelay(int index) const { return ReelDelay[index]; }
    std::vector<float>& GetReelTime() { return reelTime; }
    const std::vector<float>& GetReelTime() const { return reelTime; }
    std::vector<unsigned char>& GetReels() { return reels; }
    const std::vector<unsigned char>& GetReels() const { return reels; }
    int GetStoppingReel() const { return stoppingReel; }
    void SetStoppingReel(int value) { stoppingReel = value; }

private:    
    GameManager();
    ~GameManager();
    GameManager(const GameManager&)             = delete;
    GameManager& operator=(const GameManager&)  = delete;  

    static GameManager* instance;
    std::map<State, GameStatePtr> gameStateMap;
    GameState* currentState;

    // Reel management variables
    const float ReelDelay[4];
    std::vector<float> reelTime;
    std::vector<unsigned char> reels;
    int stoppingReel;
    
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


#endif