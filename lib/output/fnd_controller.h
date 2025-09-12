#ifndef FND_CONTROLLER_H
#define FND_CONTROLLER_H

#include <fixed_rate_updater.h>
#include <game_enums.h>
#include <vector>
#include <list>
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
    vector<unsigned char> originalDisplay;
    vector<unsigned char> outputDisplay;
    map<Animation, FNDAnimation*> animations;
    std::list<FNDAnimation*> playingAnimations;
private:
    FNDController();
    ~FNDController();
    FNDController(const FNDController&) = delete;
    FNDController& operator=(const FNDController&) = delete;
public:
    static FNDController& GetInstance();
    static void DestroyInstance();
    unsigned char GetOutputDigit(int digit);
    void SetDisplay(Letter letter, bool consecutive = true);
    void SetDisplay(int num, bool consecutive = true, int start = 0, int end = 3);
    void AddAnimation(Animation Animation, FNDAnimation* fndAnimation);
    void StartAnimation(Animation animation, float speed = 1, int start = 0, int end = 3);
    void StopAnimations();
    bool IsAnimationPlaying();
    void Update() override;
};


class FNDAnimation
{
protected:
    float speed;
    float playTime;
    int startDigit, endDigit;
    bool isAnimationPlaying;
public:
    FNDAnimation() : isAnimationPlaying(false) {}
    bool IsAnimationPlaying();
    virtual void StartAnimation(float spd, int start, int end);
    virtual void PlayAnimation(const vector<unsigned char>& original, vector<unsigned char>& output) = 0;
    virtual ~FNDAnimation() {}
};

#endif