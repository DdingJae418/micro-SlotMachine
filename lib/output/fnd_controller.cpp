#include <fnd_controller.h>
#include <avr/interrupt.h>
#include <util/delay.h>

FNDController* FNDController::Instance = nullptr;

FNDController::FNDController()
{
    // Single tone pattern
    if(Instance == nullptr)
    {
        Instance = this;
        currentDigit = 0;
        
        // Set FND pin
        DDRC = 0xFF;
        DDRG = 0x0F;

        // Initialize timer
        TCCR1A = 0; // CTC 모드 설정
        TCCR1B = (1 << WGM12) | (1 << CS12); // CTC 모드, 분주비 256
        OCR1A = 2500; // 약 1ms 간격 (16MHz / 256 / 2500 = 1ms)
        TIMSK = (1 << OCIE1A); // 타이머 비교 일치 인터럽트 활성화
        
        // Set entire area interrupt
        sei(); 
    }
}

void FNDController::SetDisplay(Letter letter)
{
    if (letter == Letter::PLAY)
    {
        while(true)
        {
            for (int i = 0; i < 4; i++) {
                PORTC = play[i];
                PORTG = fnd_select[i];
                _delay_us(2200);
            }
        }
    }
}

void FNDController::SetDisplay(int num)
{
    unsigned char fnd[4];
    fnd[0] = (num / 1000) % 10;
    fnd[1] = (num / 100) % 10;
    fnd[2] = (num / 10) % 10;
    fnd[3] = num % 10;

    for (int i = 0; i < 4; i++) 
    {
        PORTC = number[fnd[i]];
        PORTG = fnd_select[i];
        _delay_us(2200);
    }
}

void FNDController::ShowDisplay()
{
    PORTC = play[currentDigit];     // 문자 출력
    PORTG = fnd_select[currentDigit]; // 자리 선택 출력

    // 다음 자리로 이동
    currentDigit++;
    if (currentDigit >= 4) {
        currentDigit = 0; // 자리 순환
    }
}

void FNDController::SetAnimation(Animations animation, float speed)
{

}

// Continuously show FND display 
ISR(TIMER1_COMPA_vect) 
{
    //FNDController::Instance->ShowDisplay();
}