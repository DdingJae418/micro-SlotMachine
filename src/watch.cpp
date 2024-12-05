// #define F_CPU 16000000UL
// #include <avr/io.h>
// #include <avr/interrupt.h>
// #include <util/delay.h>

// #define ON 1
// #define OFF 0

// class Stopwatch {
// private:
//     unsigned char number[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; // 0-9 숫자 패턴
//     unsigned char fnd_select[4] = {0x08, 0x04, 0x02, 0x01}; // FND 자리 선택 패턴

// public:
//     volatile unsigned int timer_count = 0; // 0.1초 단위로 타이머 카운트
//     volatile unsigned char stopwatch_running = OFF;
//     volatile unsigned char timer_reset = OFF;

//     void displayTime() {
//         // 시간을 XXX.X 형식으로 변환하여 FND에 표시
//         unsigned char fnd[4];
//         fnd[0] = (timer_count / 1000) % 10;
//         fnd[1] = (timer_count / 100) % 10;
//         fnd[2] = (timer_count / 10) % 10;
//         fnd[3] = timer_count % 10;

//         for (int i = 0; i < 4; i++) {
//             PORTC = number[fnd[i]] | (i == 2 ? 0x80 : 0x00); // 소수점 추가
//             PORTG = fnd_select[i];
//             _delay_us(2200);
//         }
//     }

//     void initializeTimer() {
//         // 16비트 타이머/카운터1 설정, 0.1초 간격
//         TCCR1A = 0;
//         TCCR1B = (1 << WGM12) | (1 << CS12); // CTC 모드, 분주비 256
//         OCR1A = 6250; // 16 MHz / (256 * 10) - 1, 0.1초 간격
//         TIMSK = (1 << OCIE1A); // 타이머1 비교 일치 인터럽트 활성화
//     }

//     void initializeExternalInterrupts() {
//         // 외부 인터럽트 INT4 (PE4) 및 INT5 (PE5) 활성화, 하강 에지에서 트리거
//         EICRB = (1 << ISC41) | (1 << ISC51); // 하강 에지 트리거 설정
//         EIMSK = (1 << INT4) | (1 << INT5);   // INT4 및 INT5 활성화
//         PORTE = (1 << PE4) | (1 << PE5);     // 내부 풀업 저항 활성화
//     }

//     void updateTimer() {
//         if (stopwatch_running) {
//             timer_count++;
//         }
//         if (timer_reset) {
//             timer_count = 0;
//             timer_reset = OFF;
//         }
//     }

//     void toggleStopwatch() {
//         stopwatch_running = !stopwatch_running;
//     }

//     void resetStopwatch() {
//         stopwatch_running = OFF;
//         timer_reset = ON;
//     }
// };

// // 전역 Stopwatch 객체
// Stopwatch stopwatch;

// // // ISR은 반드시 전역 함수여야 합니다.
// // ISR(TIMER1_COMPA_vect) {
// //     stopwatch.updateTimer();
// // }


// // Get Switch 1 Input
// ISR(INT4_vect) {
//     if (!(PINE & (1 << PE4))) { // SW1이 눌린 상태 확인
//         stopwatch.toggleStopwatch(); // 스톱워치 시작 또는 일시정지
//     }
// }


// // Get Switch 2 Input
// ISR(INT5_vect) {
//     if (!(PINE & (1 << PE5))) { // SW2가 눌린 상태 확인
//         stopwatch.resetStopwatch(); // 스톱워치 정지 및 초기화
//     }
// }

// int watch() {
//     // FND 및 스위치 포트 초기화
//     DDRC = 0xFF; // FND 데이터 핀
//     DDRG = 0x0F; // FND 자리 선택 핀
//     DDRE = 0x00; // 스위치 입력 핀

//     stopwatch.initializeTimer();              // 타이머 설정
//     stopwatch.initializeExternalInterrupts(); // 외부 인터럽트 설정
//     sei();                                    // 전역 인터럽트 활성화

//     while (true) {
//         stopwatch.displayTime(); // FND에 0.1초 단위로 시간 표시
//     }

//     return 0;
// }