#ifndef GAME_ENUMS_H
#define GAME_ENUMS_H

namespace game_enums 
{
    enum class State
    {
        Ready, Opening, Playing, Stopping, Checking, Result
    };

    enum class Letter
    {
        PLAY, _1ST, _2ND, _3RD, FAIL 
    };

    enum class Animations
    {
        NONE, FADE_IN_OUT, FLICKER
    };
}

#endif