#include <avr/interrupt.h>
#include <util/delay.h>
#include "fnd_controller.h"


/*** Const Variables ***/
const vector<unsigned char> number = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
const vector<unsigned char> play = {0x73, 0x38, 0x77, 0x6E};


FNDController::FNDController()
    : originalDisplay(4, 0), outputDisplay(4, 0), currentAnimation(nullptr)
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
    case Letter::NONE :
        std::fill(originalDisplay.begin(), originalDisplay.end(), 0);
        break;
    case Letter::PLAY :
        originalDisplay = play;
        break;
    default:
        break;
    }

    // Empty output display
    if (!consecutive)
        std::fill(outputDisplay.begin(), outputDisplay.end(), 0);
}

void FNDController::SetDisplay(int num, bool consecutive)
{
    // Set original display
    originalDisplay[0] = number[(num / 1000) % 10];
    originalDisplay[1] = number[(num / 100) % 10];
    originalDisplay[2] = number[(num / 10) % 10];
    originalDisplay[3] = number[num % 10];

    // Empty output display
    if (!consecutive)
        std::fill(outputDisplay.begin(), outputDisplay.end(), 0);
}

void FNDController::AddAnimation(Animation animation, FNDAnimation* fndAnimation)
{
    animationMap[animation] = fndAnimation;
}

void FNDController::StartAnimation(Animation animation, float speed, int start, int end)
{
    currentAnimation = animationMap[animation];
    currentAnimation->StartAnimation(speed, start, end);
}

bool FNDController::IsAnimationPlaying()
{
    return currentAnimation && currentAnimation->IsAnimationPlaying();
}

void FNDController::Update()
{
    if(currentAnimation && currentAnimation->IsAnimationPlaying())
        currentAnimation->PlayAnimation(originalDisplay, outputDisplay);
}

FNDController::~FNDController()
{
    for (auto a : animationMap)
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