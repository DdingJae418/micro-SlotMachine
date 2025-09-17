#ifndef SOUNDS_H
#define SOUNDS_H

#include <vector>
#include <utility>
#include "note_frequency.h"

using BuzzerSound = std::vector<std::pair<double, float>>;
using NoteIter = BuzzerSound::const_iterator;

namespace sounds
{
    // Zenonia3 ost
    inline const BuzzerSound ReadySong = {
        {NoteFs5, 1.5}, {NoteG5, 0.5}, {NoteA5, 2.95}, {NoteRest, 0.05}, {NoteA5, 0.5},
        {NoteG5, 0.5}, {NoteFs5, 0.5}, {NoteG5, 0.5}, {NoteA5, 0.5}, {NoteCs6, 0.5},
        {NoteD6, 4}, {NoteRest, 1}, {NoteA5, 1}, {NoteE6, 1.5}, {NoteD6, 0.45}, 
        {NoteRest, 0.05}, {NoteD6, 2.9}, {NoteRest, 0.1}, {NoteB5, 1}, {NoteA5, 1}, 
        {NoteB5, 1}, {NoteFs5, 0.2}, {NoteE5, 1.3}, {NoteD5, 0.45}, {NoteRest, 0.05},  
        {NoteD5, 2}, {NoteB4, 1.5}, {NoteD5, 0.5}, {NoteFs5, 2}, {NoteG5, 1.9},
        {NoteRest, 0.1}
    };

    inline const BuzzerSound StartSound = {
        {NoteC5, 0.5}, {NoteD5, 0.5}, {NoteE5, 0.5}, {NoteF5, 0.5}, {NoteG5, 4}
    };

    inline const BuzzerSound ReelSound = {
        {NoteC5, 0.5}
    };

    inline const BuzzerSound StartPlayingSound = {
        {NoteG5, 1}, {NoteRest, 0.5}, {NoteG5, 1}, {NoteRest, 0.5}, {NoteG5, 3}
    };

    inline const BuzzerSound PlayingSong = {
        {NoteC5, 0.5}, {NoteE5, 0.5}, {NoteG5, 0.5}, {NoteC6, 0.5}, {NoteRest, 0.2},
        {NoteC6, 0.5}, {NoteG5, 0.5}, {NoteE5, 0.5}, {NoteC5, 0.5}, {NoteRest, 0.2},
        {NoteD5, 0.5}, {NoteF5, 0.5}, {NoteA5, 0.5}, {NoteD6, 0.5}, {NoteRest, 0.2},
        {NoteD6, 0.5}, {NoteA5, 0.5}, {NoteF5, 0.5}, {NoteD5, 0.5}, {NoteRest, 0.2},
        {NoteE5, 0.5}, {NoteG5, 0.5}, {NoteB5, 0.5}, {NoteE6, 0.5}, {NoteRest, 0.2},
        {NoteE6, 0.5}, {NoteB5, 0.5}, {NoteG5, 0.5}, {NoteE5, 0.5}, {NoteRest, 0.2},
        {NoteC6, 1.0}, {NoteB5, 0.5}, {NoteA5, 0.5}, {NoteRest, 0.2},
        {NoteA5, 0.5}, {NoteG5, 0.5}, {NoteF5, 0.5}, {NoteE5, 0.5}, {NoteRest, 0.2}
    };

    inline const BuzzerSound ResetSound = {
        {NoteG5, 0.5}, {NoteF5, 0.5}, {NoteE5, 0.5}, {NoteD5, 0.5}, {NoteC5, 4}
    };

    inline const BuzzerSound LeverSound = {
        {NoteRest, 0.2}, {NoteD6, 0.5}, {NoteG6, 0.5}
    };

    // Reverse sound of the LeverSound
    inline const BuzzerSound ReelStopSound(LeverSound.rbegin(), LeverSound.rend());

    inline const BuzzerSound FailSound = {
        {NoteE5, 0.5}, {NoteDs5, 0.5}, {NoteD5, 0.5}, {NoteCs5, 1}
    };

    inline const BuzzerSound SuccessSound = {
        {NoteG6, 0.5}, {NoteRest, 0.1}, {NoteG6, 0.2}, {NoteRest, 0.1}, {NoteG6, 0.2}, 
        {NoteRest, 0.1}, {NoteG6, 1.5}, {NoteRest, 0.1}, {NoteA6, 0.75}, {NoteG6, 0.85}, 
        {NoteA6, 0.9}, {NoteB6, 0.6}, {NoteRest, 0.1}, {NoteB6, 0.3}, {NoteRest, 0.1}, 
        {NoteB6, 0.3}, {NoteRest, 0.1}, {NoteB6, 3}
    };
}


#endif