#ifndef FND_CONTROLLER_H
#define FND_CONTROLLER_H

#include <fixed_rate_updater.h>
#include <game_enums.h>
#include <vector>
#include <map>

using std::vector;
using std::map;
using game_enums::Letter;
using game_enums::Animation;

class FNDAnimation;


class FNDController : public UpdateListener
{
private:
    static FNDController* instance;
    vector<unsigned char> displayOutput;
    map<Animation, FNDAnimation*> animationMap;
    FNDAnimation* currentAnimation;
    FNDController() : displayOutput(4, 0), currentAnimation(nullptr) {}
public:
    static FNDController* GetInstance();
    unsigned char GetDisplayDigit(int digit);
    void SetDisplay(Letter letter);
    void SetDisplay(int num);
    void AddAnimation(Animation Animation, FNDAnimation* fndAnimation);
    void SetAnimation(Animation animation, float speed = 0);
    virtual void Update();
    ~FNDController();
};


class FNDAnimation
{
protected:
    float speed;
public:
    FNDAnimation() : speed(0) {}
    void InitializeAnimation(float _speed);
    virtual void PlayAnimation(vector<unsigned char>& display) = 0;
    virtual ~FNDAnimation() {}
};

#endif