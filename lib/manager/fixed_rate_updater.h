#ifndef FIXED_RATE_UPDATER_H
#define FIXED_RATE_UPDATER_H

#include <vector>

class UpdateListener;

class FixedRateUpdater
{
private:
    static FixedRateUpdater* instance; 
    std::vector<UpdateListener*> listeners;
    int frameRate;
    volatile bool updateFlag;
    FixedRateUpdater() : frameRate(60), updateFlag(false) {}
public:
    static FixedRateUpdater* GetInstance();
    ~FixedRateUpdater();
    void AddListener(UpdateListener* listener);
    void CallListeners();
    void SetFrameRate(int rate);
    int GetFrameRate();
    void SetUpdateFlag();
};

class UpdateListener
{
public:
    virtual void Update() = 0;
    virtual ~UpdateListener() {}
};

#endif