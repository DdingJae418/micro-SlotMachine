#include "fnd_animations.h"
#include <algorithm>

/**** No Animation ****/

void PlainAnimation::PlayAnimation(const vector<unsigned char>& original, vector<unsigned char>& output)
{
    // Just output original display
    std::copy(original.begin() + startDigit, original.begin() + endDigit + 1, output.begin() + startDigit);

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



/**** Flicker Animation *****/

void FlickerAnimation::StartAnimation(float speed, int start, int end)
{
    FNDAnimation::StartAnimation(speed, start, end);
    timeGap = 1 / speed;
    turnOn = true;
    flickerCount = 0;
}

void FlickerAnimation::PlayAnimation(const vector<unsigned char>& original, vector<unsigned char>& output)
{
    if (turnOn)
    {
        std::copy(original.begin() + startDigit, original.begin() + endDigit + 1, output.begin() + startDigit);
    }
    else
    {
        std::fill(output.begin() + startDigit, output.begin() + endDigit + 1, 0);
    }

    playTime += Time::DeltaTime();
    if(playTime > timeGap)
    {
        playTime = 0;
        turnOn = !turnOn;
        flickerCount++;

        if(flickerCount == 7) isAnimationPlaying = false;
    }
}



/**** Round Robin Animation ****/
void RoundRobinAnimation::StartAnimation(float speed, int start, int end)
{
    FNDAnimation::StartAnimation(speed, start, end);
    currentDigit = startDigit;
    timeGap = 1 / speed;
    playTime = timeGap;
    movingRight = true;
    roundCount = 0;
}

void RoundRobinAnimation::PlayAnimation(const vector<unsigned char>& original, vector<unsigned char>& output)
{
    // Count second
    playTime += Time::DeltaTime();

    if(playTime > timeGap)
    {
        if (roundCount > 1)
        {
            isAnimationPlaying = false;
            std::fill(output.begin() + startDigit, output.begin() + endDigit + 1, 0);
            return;
        }

        // Turn currentDigit on, end turn off others
        std::fill(output.begin() + startDigit, output.begin() + endDigit + 1, 0);
        output[currentDigit] = original[currentDigit];

        // Move to next digit
        if(movingRight)
        {        
            currentDigit++;
            if (currentDigit > endDigit)
            {
                currentDigit--;
                movingRight = false;
            }
        }
        else
        {
            currentDigit--;
            if(currentDigit < startDigit)
            {
                roundCount++;
                movingRight = true;
            }
        }
        playTime = 0;
    }
}