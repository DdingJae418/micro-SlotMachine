#ifndef FIXED_RATE_UPDATER_H
#define FIXED_RATE_UPDATER_H

#include <vector>

class UpdateListener;

class FixedRateUpdater
{
private:
    std::vector<UpdateListener*> listeners;
    int frameRate;
    volatile bool updateFlag;
private:
    FixedRateUpdater();
    ~FixedRateUpdater() = default;
    FixedRateUpdater(const FixedRateUpdater&) = delete;
    FixedRateUpdater& operator= (const FixedRateUpdater&) = delete;
public:
    static FixedRateUpdater& GetInstance();
    void AddListener(UpdateListener* listener);
    void CallListeners();
    void SetFrameRate(int rate);
    int GetFrameRate();
    void SetUpdateFlag();
};

class Time
{
public:
    static float DeltaTime();
};

class UpdateListener
{
public:
    virtual void Update() = 0;
    virtual ~UpdateListener() {}
};

#endif