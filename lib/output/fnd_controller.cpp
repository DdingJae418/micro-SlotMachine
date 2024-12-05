#include <avr/interrupt.h>
#include <util/delay.h>
#include "fnd_controller.h"


/*** Const Variables ***/
const vector<unsigned char> number = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
const vector<unsigned char> play = {0x73, 0x38, 0x77, 0x6E};


FNDController* FNDController::GetInstance()
{
    if(!instance)
    {
        instance = new FNDController();
        
        // Set FND pin
        DDRC = 0xFF;
        DDRG = 0x0F;

        // Set timer0 for FND
        TCCR0 = (1 << WGM01) | (1 << CS02);
        OCR0 = 124; // 2ms
        TIMSK |= (1 << OCIE0);

        sei(); 
    }
    return instance;
}

unsigned char FNDController::GetDisplayDigit(int digit)
{
    return displayOutput[digit];
}

void FNDController::SetDisplay(Letter letter)
{
    if (letter == Letter::PLAY) displayOutput = play;
}

void FNDController::SetDisplay(int num)
{
    displayOutput[0] = number[(num / 1000) % 10];
    displayOutput[1] = number[(num / 100) % 10];
    displayOutput[2] = number[(num / 10) % 10];
    displayOutput[3] = number[num % 10];
}

void FNDController::AddAnimation(Animation animation, FNDAnimation* fndAnimation)
{
    animationMap[animation] = fndAnimation;
}

void FNDController::SetAnimation(Animation animation, float speed)
{
    if (animation == Animation::NONE)
        currentAnimation = nullptr;
    else
    {
        currentAnimation = animationMap[animation];
        currentAnimation->InitializeAnimation(speed);
    }
}

void FNDController::Update()
{
    if(currentAnimation)
        currentAnimation->PlayAnimation(displayOutput);
}

FNDController::~FNDController()
{
    for (auto a : animationMap)
        delete a.second;
}

FNDController* FNDController::instance = nullptr;

void FNDAnimation::InitializeAnimation(float _speed)
{
    speed = _speed;
}



// Show FND display on every timer interrupt
unsigned char fnd_select[4] = {0x08, 0x04, 0x02, 0x01};
volatile int currentDigit = 0;

ISR(TIMER0_COMP_vect) {
    PORTC = FNDController::GetInstance()->GetDisplayDigit(currentDigit);
    PORTG = fnd_select[currentDigit];
    
    currentDigit++;
    if (currentDigit >= 4) {
        currentDigit = 0;
    }
}