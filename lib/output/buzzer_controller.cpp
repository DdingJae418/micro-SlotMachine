#include <avr/interrupt.h>
#include <util/delay.h>
#include "buzzer_controller.h"

BuzzerController::BuzzerController() 
    : currentSound(nullptr), currentNote(nullptr), isMute(false)
{
    // Set buzzer pin
    DDRB |= (1 << PB4);
    sei();
}

BuzzerController& BuzzerController::GetInstance()
{
    static BuzzerController instance;
    return instance;
}

void BuzzerController::StartSound(const BuzzerSound* sound, float speed, bool loop)
{
    if(isMute) return;

    currentSound = sound;
    playSpeed = speed;
    loopSound = loop;
    playTime = 0;

    // Play first note
    if (currentSound) 
    {
        currentNote = currentSound->begin();
        PlayNote(currentNote->first);
    }
}

void BuzzerController::Update()
{
    if (!currentSound) return;

    playTime += playSpeed * Time::DeltaTime();
    if (playTime >= currentNote->second)
    {
        currentNote++;

        if (currentNote == currentSound->end()) 
        // Playing complete
        {
            if (loopSound) 
                StartSound(currentSound, playSpeed, true);
            else 
            {
                currentSound = nullptr;
                PlayNote(NOTE_REST);
            }
        }
        else
        // Play next note
        {
            PlayNote(currentNote->first);
            playTime = 0;
        }
    }
}

void BuzzerController::PlayNote(double frequency)
{
    // Stop buzzer
    if (frequency == 0) 
    {
        TCCR2 = 0;
        TIMSK &= ~(1 << OCIE2);
        PORTB &= ~(1 << PB4);
        return;
    }

    // Activate timer2 with 256 prescaler
    OCR2 = static_cast<uint8_t>((F_CPU / (256.0 * frequency)) - 1);
    TCCR2 = (1 << WGM21) | (1 << CS22);                            
    TIMSK |= (1 << OCIE2);                        
}

bool BuzzerController::IsSoundPlaying()
{
    return currentSound;
}

void BuzzerController::MuteBuzzer(bool value)
{
    isMute = value;
}

// Play buzzer with timer2 interrupt
ISR(TIMER2_COMP_vect) 
{
    PORTB ^= (1 << PB4);
}