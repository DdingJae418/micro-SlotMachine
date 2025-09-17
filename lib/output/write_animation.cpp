#include "fnd_animations.h"
#include <vector>
#include <utility>

const WordSequence failSequence = {{0, 0x20}, {0, 0x30}, {0, 0x31}, {0, 0x71}, {1, 0x20}, {1, 0x30},
    {1, 0x31}, {1, 0x33}, {1, 0x37}, {1, 0x77}, {2, 0x02}, {2, 0x06}, {3, 0x20}, {3, 0x30},
    {3, 0x38}
};

const WordSequence firstSequence = {{0, 0x00}, {1, 0x20}, {1, 0x30}, {2, 0x01}, {2, 0x21}, {2, 0x61},
    {2, 0x65}, {2, 0x6d}, {3, 0x40}, {3, 0x60}, {3, 0x70}, {3, 0x78}, {3, 0xf8}
};

const WordSequence secondSequence = {{0, 0x00}, {1, 0x01}, {1, 0x03}, {1, 0x43}, {1, 0x53}, {1, 0x5b},
    {2, 0x10}, {2, 0x50}, {2, 0x54}, {3, 0x40}, {3, 0x50}, {3, 0x58}, {3, 0x5a}, {3, 0x5e},
    {3, 0xde}
};

const WordSequence thirdSequence = {{0, 0x00}, {1, 0x01}, {1, 0x03}, {1, 0x43}, {1, 0x47}, {1, 0x4f},
    {2, 0x10}, {2, 0x50}, {3, 0x40}, {3, 0x50}, {3, 0x58}, {3, 0x5a}, {3, 0x5e}, {3, 0xde}
};


void WriteAnimation::StartAnimation(float speed, int start, int end)
{
    FNDAnimation::StartAnimation(speed, start, end);

    currentDigit = startDigit;
    timeGap = 1/speed;
}

void WriteAnimation::PlayAnimation(const vector<unsigned char>& _, vector<unsigned char>& output)
{
    playTime += Time::DeltaTime();

    if (playTime > timeGap)
    {
        currentDigit = currentIter->first;
        output[currentDigit] = currentIter->second;
        currentIter++;

        if (currentIter == currentSeq->end())
            isAnimationPlaying = false;
        
        playTime = 0;
    }
}


void WriteFailAnimation::StartAnimation(float speed, int start, int end)
{
    WriteAnimation::StartAnimation(speed, start, end);
    currentSeq = &failSequence;
    currentIter = failSequence.begin();
}

void Write1stAnimation::StartAnimation(float speed, int start, int end)
{
    WriteAnimation::StartAnimation(speed, start, end);
    currentSeq = &firstSequence;
    currentIter = firstSequence.begin();
}

void Write2ndAnimation::StartAnimation(float speed, int start, int end)
{
    WriteAnimation::StartAnimation(speed, start, end);
    currentSeq = &secondSequence;
    currentIter = secondSequence.begin();
}

void Write3rdAnimation::StartAnimation(float speed, int start, int end)
{
    WriteAnimation::StartAnimation(speed, start, end);
    currentSeq = &thirdSequence;
    currentIter = thirdSequence.begin();
}