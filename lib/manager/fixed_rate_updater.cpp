#include <avr/interrupt.h>
#include <util/delay.h>
#include "fixed_rate_updater.h"

/*** Define Fixed Rate Updater ***/

FixedRateUpdater* FixedRateUpdater::GetInstance()
{
    if(!instance)
    {
        instance = new FixedRateUpdater();

        // Initialize timer
        TCCR1A = 0;
        TCCR1B = (1 << WGM12) | (1 << CS12);
        OCR1A = 1040; // 60fps
        TIMSK = (1 << OCIE1A);
        sei(); 
    }
    return instance;
}

FixedRateUpdater::~FixedRateUpdater()
{
    delete instance;
}

void FixedRateUpdater::AddListener(UpdateListener* listener)
{
    listeners.push_back(listener);
}

void FixedRateUpdater::CallListeners()
{
    // Update only when update flag is set
    if (updateFlag)
    {
        for (auto& listener : listeners)
            listener->Update();
        updateFlag = false;
    }
}

void FixedRateUpdater::SetFrameRate(int rate)
{
    frameRate = rate;
        
    constexpr int TIMER_CLOCK = 16000000; // 16 MHz
    constexpr int PRESCALER = 256;

    OCR1A = (TIMER_CLOCK / (PRESCALER * frameRate)) - 1;

    if (OCR1A < 1) {
        OCR1A = 1; // Minimum possible value
    }
}

int FixedRateUpdater::GetFrameRate()
{
    return frameRate;
}

void FixedRateUpdater::SetUpdateFlag()
{
    updateFlag = true;
}

FixedRateUpdater* FixedRateUpdater::instance = nullptr;


/*** Timer Interrupt ***/

ISR(TIMER1_COMPA_vect) 
{
    // Set fixed update flag
    FixedRateUpdater::GetInstance()->SetUpdateFlag();
}