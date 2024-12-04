#ifndef FND_CONTROLLER_H
#define FND_CONTROLLER_H

#include <fixed_rate_updater.h>
#include <game_enums.h>
#include <vector>

using std::vector;
using game_enums::Letter;
using game_enums::Animation;


class FNDController : public UpdateListener
{
private:
    static FNDController* instance;
    vector<unsigned char> currentScreen;
    Animation currentAnimation;
    float animationSpeed;
    FNDController() : currentScreen(4) {}
public:
    static FNDController* GetInstance();
    void SetDisplay(Letter letter);
    void SetDisplay(int num);
    void SetAnimation(Animation animation, float speed);
    void ShowDisplay();
    virtual void Update();
};


#endif