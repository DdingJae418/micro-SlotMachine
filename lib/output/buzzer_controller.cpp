#include <avr/interrupt.h>
#include <util/delay.h>
#include "buzzer_controller.h"
#include "note_frequency.h"


BuzzerController* BuzzerController::GetInstance()
{
    if(!instance)
    {
        instance = new BuzzerController();

        // Set buzzer pin
        DDRB |= (1 << PB4);
        sei();
    }
    return instance;
}

void BuzzerController::PlayNote(uint16_t frequency)
{
    // Stop buzzer
    if (frequency == 0) 
    {
        TCCR2 = 0;
        TIMSK &= ~(1 << OCIE2);
        PORTB &= ~(1 << PB4);
        return;
    }

    // Activate timer2
    OCR2 = (F_CPU / (2 * 64 * frequency)) - 1;
    TCCR2 = (1 << WGM01) | (1 << CS01) | (1 << CS00);
    TIMSK |= (1 << OCIE2);                            
}

void BuzzerController::Update()
{
    playTime += Time::DeltaTime();
    if (playTime < 3)
        PlayNote(NOTE_A2);
    else
        PlayNote(NOTE_REST);
}

BuzzerController* BuzzerController::instance = nullptr;


// Play buzzer with timer2 interrupt
ISR(TIMER2_COMP_vect) 
{
    PORTB ^= (1 << PB4);
}