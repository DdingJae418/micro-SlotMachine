#include <avr/interrupt.h>
#include <util/delay.h>
#include "fixed_rate_updater.h"

/*** Define Fixed Rate Updater ***/

FixedRateUpdater::FixedRateUpdater() : frameRate(60), updateFlag(false)
{
    // Initialize timer1 for fixed update
    TCCR1A = 0;
    TCCR1B = (1 << WGM12) | (1 << CS12);
    OCR1A = 1040; // 60fps
    TIMSK |= (1 << OCIE1A);
    sei(); 
}

FixedRateUpdater& FixedRateUpdater::GetInstance()
{
    if(!instance) instance = new FixedRateUpdater();
    return *instance;
}

void FixedRateUpdater::DestroyInstance()
{
    delete instance;
    instance = nullptr;
}

void FixedRateUpdater::AddListener(UpdateListener* listener)
{
    if (listener != nullptr)
    {
        listeners.push_back(listener);
    }
}

void FixedRateUpdater::CallListeners()
{
    if (updateFlag)
    {
        for (UpdateListener* listener : listeners)
        {
            if (listener)
                listener->Update();
        }
        updateFlag = false;
    }
}

void FixedRateUpdater::SetFrameRate(int rate)
{
    frameRate = rate;

    OCR1A = ( F_CPU / (256 * frameRate)) - 1;

    if (OCR1A < 1) {
        OCR1A = 1; // Minimum possible value
    }
}

int FixedRateUpdater::GetFrameRate() const
{
    return frameRate;
}

void FixedRateUpdater::SetUpdateFlag()
{
    updateFlag = true;
}

FixedRateUpdater* FixedRateUpdater::instance = nullptr;

float Time::DeltaTime()
{
    static float frame = FixedRateUpdater::GetInstance().GetFrameRate();
    return 1 / frame;
}


// Timer interrupt
ISR(TIMER1_COMPA_vect) 
{
    // Set fixed update flag
    static FixedRateUpdater& updater = FixedRateUpdater::GetInstance();
    updater.SetUpdateFlag();
}