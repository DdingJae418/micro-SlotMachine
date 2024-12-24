#ifndef GAME_ENUMS_H
#define GAME_ENUMS_H

namespace game_enums 
{
    enum class State
    {
        READY, OPENING, PLAYING, STOPPING, RESULT, RESETTING
    };

    enum class Letter
    {
        NONE, PLAY, _1ST, _2ND, _3RD, FAIL 
    };

    enum class Animation
    {
        NONE, SWIPE, FLICKER, ROUND_ROBIN, WRITE_FAIL, WRITE_1ST, WRITE_2ND, WRITE_3RD
    };

    enum class Switch
    {
        ONE, TWO
    };
}

#endif