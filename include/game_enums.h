#ifndef GAME_ENUMS_H
#define GAME_ENUMS_H

namespace game_enums 
{
    enum class State
    {
        READY, OPENING, PLAYING, STOPPING, CHECKING, RESULT
    };

    enum class Letter
    {
        PLAY, _1ST, _2ND, _3RD, FAIL 
    };

    enum class Animation
    {
        NONE, FADE, FLICKER
    };
}

#endif