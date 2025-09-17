#ifndef FND_ANIMATIONS_H
#define FND_ANIMATIONS_H

#include <fnd_controller.h>

using WordSequence = const std::vector<std::pair<int, unsigned char>>;
using WordIter = std::vector<std::pair<int, unsigned char>>::const_iterator;

class PlainAnimation : public FNDAnimation
{
public:
    void PlayAnimation(const vector<unsigned char>& original, vector<unsigned char>& output) override;
};

class SwipeAnimation : public FNDAnimation
{
public:
    void StartAnimation(float speed, int start, int end) override;
    void PlayAnimation(const vector<unsigned char>& original, vector<unsigned char>& output) override;

private:
    int currentDigit;
    int currentCol;
    float timeGap;
};

class FlickerAnimation : public FNDAnimation
{
public:
    void StartAnimation(float speed, int start, int end) override;
    void PlayAnimation(const vector<unsigned char>& original, vector<unsigned char>& output) override;

private:
    float timeGap;
    bool turnOn;
    int flickerCount;
};

class RoundRobinAnimation : public FNDAnimation
{
public:
    void StartAnimation(float speed, int start, int end) override;
    void PlayAnimation(const vector<unsigned char>& original, vector<unsigned char>& output) override;

private:
    int currentDigit;
    float timeGap;
    bool movingRight;
    int roundCount;
};

class WriteAnimation : public FNDAnimation
{
public:
    void StartAnimation(float speed, int start, int end) override;
    void PlayAnimation(const vector<unsigned char>& _, vector<unsigned char>& output) override;

protected:
    WordSequence* currentSeq;
    WordIter currentIter;

private:
    int currentDigit;
    float timeGap;
};

class WriteFailAnimation : public WriteAnimation
{
public:
    void StartAnimation(float speed, int start, int end) override;
};

class Write1stAnimation : public WriteAnimation
{
public:
    void StartAnimation(float speed, int start, int end) override;
};

class Write2ndAnimation : public WriteAnimation
{
public:
    void StartAnimation(float speed, int start, int end) override;
};

class Write3rdAnimation : public WriteAnimation
{
public:
    void StartAnimation(float speed, int start, int end) override;
};



#endif