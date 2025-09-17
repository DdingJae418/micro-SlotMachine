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

class RoundRobinAnimation : public FNDAnimation
{
private:
    int currentDigit;
    float timeGap;
    bool movingRight;
    int roundCount;
public:
    void StartAnimation(float speed, int start, int end) override;
    void PlayAnimation(const vector<unsigned char>& original, vector<unsigned char>& output) override;
};

class WriteAnimation : public FNDAnimation
{
private:
    int currentDigit;
    float timeGap;
protected:
    WordSequence* currentSeq;
    WordIter currentIter;
public:
    void StartAnimation(float speed, int start, int end) override;
    void PlayAnimation(const vector<unsigned char>& _, vector<unsigned char>& output) override;
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