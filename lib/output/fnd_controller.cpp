#include <avr/interrupt.h>
#include <util/delay.h>
#include "fnd_controller.h"


/*** Const Variables ***/
const vector<unsigned char> number = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
const vector<unsigned char> play = {0x73, 0x38, 0x77, 0x6E};
const vector<unsigned char> fail = {0x71, 0x77, 0x06, 0x38};
const vector<unsigned char> _1st = {0x00, 0x30, 0x6d, 0xf8};
const vector<unsigned char> _2nd = {0x00, 0x5b, 0x54, 0xde};
const vector<unsigned char> _3rd = {0x00, 0x4f, 0x50, 0xde};


FNDController::FNDController()
    : originalDisplay(4, 0), outputDisplay(4, 0)
{
    // Set FND pin
    DDRC = 0xFF;
    DDRG = 0x0F;

    // Set timer0 for FND
    TCCR0 = (1 << WGM01) | (1 << CS02);
    OCR0 = 124; // 2ms
    TIMSK |= (1 << OCIE0);
}

FNDController& FNDController::GetInstance()
{
    if (!instance) instance = new FNDController();
    return *instance;
}

void FNDController::DestroyInstance()
{
    delete instance;
    instance = nullptr;
}

unsigned char FNDController::GetOutputDigit(int digit)
{
    return outputDisplay[digit];
}

void FNDController::SetDisplay(Letter letter, bool consecutive)
{
    // Set original display
    switch (letter)
    {
    case Letter::None:
        std::fill(originalDisplay.begin(), originalDisplay.end(), 0);
        break;
    case Letter::Play:
        originalDisplay = play;
        break;
    case Letter::Fail:
        originalDisplay = fail;
        break;
    case Letter::_1st:
        originalDisplay = _1st;
        break;
    case Letter::_2nd:
        originalDisplay = _2nd;
        break;
    case Letter::_3rd:
        originalDisplay = _3rd;
        break;
    default:
        break;
    }

    // Empty output display
    if (!consecutive)
        std::fill(outputDisplay.begin(), outputDisplay.end(), 0);
}

void FNDController::SetDisplay(int num, bool consecutive, int start, int end)
{
    // Set original display
    for (int i = start; i <= end; i++) {
        int divisor = 1;
        for (int j = 0; j < (3 - i); j++) divisor *= 10;
        originalDisplay[i] = number[(num / divisor) % 10];
    }

    // Empty output display
    if (!consecutive)
        std::fill(outputDisplay.begin() + start, outputDisplay.begin() + end + 1, 0);
}

void FNDController::AddAnimation(Animation animation, FNDAnimation* fndAnimation)
{
    if (animations.find(animation) == animations.end())
    {
        animations.insert({animation, fndAnimation});
    }
}

void FNDController::StartAnimation(Animation animation, float speed, int start, int end)
{
    auto iter = animations.find(animation);
    if (iter != animations.end())
    {
        iter->second->StartAnimation(speed, start, end);
        playingAnimations.push_back(iter->second);
    }
}

void FNDController::StopAnimations()
{
    // Clear every animations
    playingAnimations.clear();
}

bool FNDController::IsAnimationPlaying()
{
    bool playing = false;
    for (auto ani : playingAnimations)
        if(ani->IsAnimationPlaying())
            playing = true;
    return playing;
}

void FNDController::Update()
{
    for (auto iter = playingAnimations.begin(); iter != playingAnimations.end(); )
    {
        if((*iter)->IsAnimationPlaying())
        {
            (*iter)->PlayAnimation(originalDisplay, outputDisplay);
            iter++;
        }
        else
        {
            iter = playingAnimations.erase(iter);
        }
    }
}

FNDController::~FNDController()
{
    for (auto a : animations)
        delete a.second;
}

FNDController* FNDController::instance = nullptr;

void FNDAnimation::StartAnimation(float spd, int start, int end)
{
    speed = spd;
    playTime = 0;
    startDigit = start;
    endDigit = end;
    isAnimationPlaying = true;
}

bool FNDAnimation::IsAnimationPlaying()
{
    return isAnimationPlaying;
}



// Show FND display on every timer interrupt
unsigned char fnd_select[4] = {0x08, 0x04, 0x02, 0x01};
volatile int currentDigit = 0;

ISR(TIMER0_COMP_vect) 
{
    static FNDController& fndController = FNDController::GetInstance();
    
    PORTC = fndController.GetOutputDigit(currentDigit);
    PORTG = fnd_select[currentDigit];
    
    currentDigit++;
    if (currentDigit >= 4) {
        currentDigit = 0;
    }
}