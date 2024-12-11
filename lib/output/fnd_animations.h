#ifndef NO_ANIMATION_H
#define NO_ANIMATION_H

#include <fnd_controller.h>

class NoAnimation : public FNDAnimation
{
public:
    void PlayAnimation(const vector<unsigned char>& original, vector<unsigned char>& output) override;
};

class SwipeAnimation : public FNDAnimation
{
private:
    int currentDigit;
    int currentCol;
    float timeGap;
public:
    void StartAnimation(float speed, int start, int end) override;
    void PlayAnimation(const vector<unsigned char>& original, vector<unsigned char>& output) override;
};

class FlickerAnimation : public FNDAnimation
{
private:
    float timeGap;
    bool turnOn;
    int flickerCount;
public:
    void StartAnimation(float speed, int start, int end) override;
    void PlayAnimation(const vector<unsigned char>& original, vector<unsigned char>& output) override;
};

#endif