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
        NONE, PLAY, _1ST, _2ND, _3RD, FAIL 
    };

    enum class Animation
    {
        NONE, SWIPE, FLICKER
    };

    enum class Sound
    {
        READY_SONG
    };

    enum class Switch
    {
        ONE, TWO
    };
}

#endif