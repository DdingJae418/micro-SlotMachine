#ifndef NO_ANIMATION_H
#define NO_ANIMATION_H

#include <fnd_controller.h>

class FadeAnimation : public FNDAnimation
{
public:
    virtual void PlayAnimation(vector<unsigned char>& display);
};

class FlickerAnimation : public FNDAnimation
{
public:
    virtual void PlayAnimation(vector<unsigned char>& display);
};

#endif