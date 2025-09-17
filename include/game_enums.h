#ifndef GAME_ENUMS_H
#define GAME_ENUMS_H

namespace game_enums 
{
    enum class State
    {
        Ready, Opening, Playing, Stopping, Result, Resetting
    };

    enum class Letter
    {
        None, Play, _1st, _2nd, _3rd, Fail 
    };

    enum class Animation
    {
        Plain, Swipe, Flicker, RoundRobin, WriteFail, Write1st, Write2nd, Write3rd
    };

    enum class Switch
    {
        One, Two
    };
}

#endif