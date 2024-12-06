#include "fnd_animations.h"

/**** No Animation ****/

void NoAnimation::PlayAnimation(const vector<unsigned char>& original, vector<unsigned char>& output)
{
    // Just output original display
    output = original;

    // End animation
    isAnimationPlaying = false;
}


/**** Swipe Animation *****/

void SwipeAnimation::StartAnimation(float speed, int start, int end)
{
    FNDAnimation::StartAnimation(speed, start, end);
    
    currentDigit = startDigit;
    currentCol = 0;
    timeGap = 1 / speed;
}

void SwipeAnimation::PlayAnimation(const vector<unsigned char>& original, vector<unsigned char>& output)
{
    // Count second
    playTime += Time::DeltaTime();

    if(playTime > timeGap)
    {
        // Turn col on
        unsigned char temp1, temp2;
        if (currentCol == 0)
        {
            temp1 = original[currentDigit] & 0x30;
            temp2 = output[currentDigit] & 0x4f;
        }
        else if(currentCol == 1)
        {
            temp1 = original[currentDigit] & 0x79;
            temp2 = output[currentDigit] & 0x06;
        }
        else
        {
            temp1 = original[currentDigit] & 0x7f;
            temp2 = 0x00;
        }
        output[currentDigit] = temp1 | temp2;

        // Move to next col
        currentCol++;
        if (currentCol >= 3)
        {
            currentDigit++;
            currentCol = 0;
        }
        playTime = 0;

        // End animation
        if(currentDigit > endDigit) isAnimationPlaying = false;
    }
}