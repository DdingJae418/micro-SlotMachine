#include <avr/interrupt.h>
#include <util/delay.h>
#include "fnd_controller.h"

/*** Const Variables ***/
const vector<unsigned char> number = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
const vector<unsigned char> fnd_select = {0x08, 0x04, 0x02, 0x01};
const vector<unsigned char> play = {0x73, 0x38, 0x77, 0x6E};


FNDController* FNDController::GetInstance()
{
    if(!instance)
    {
        instance = new FNDController();
        
        // Set FND pin
        DDRC = 0xFF;
        DDRG = 0x0F;
        sei(); 
    }
    return instance;
}

void FNDController::SetDisplay(Letter letter)
{
    if (letter == Letter::PLAY) currentScreen = play;
}

void FNDController::SetDisplay(int num)
{
    currentScreen[0] = (num / 1000) % 10;
    currentScreen[1] = (num / 100) % 10;
    currentScreen[2] = (num / 10) % 10;
    currentScreen[3] = num % 10;
}

void FNDController::SetAnimation(Animation animation, float speed)
{
    currentAnimation = animation;
    animationSpeed = speed;
}

void FNDController::ShowDisplay()
{

}

void FNDController::Update()
{

}

FNDController* FNDController::instance = nullptr;