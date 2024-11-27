#ifndef FND_CONTROLLER_H
#define FND_CONTROLLER_H

#include <game_enums.h>

using game_enums::Letter;
using game_enums::Animations;


/**
 * @brief Utility class to output number or letter at the FND display
 */
class FNDController
{
private:
    const unsigned char number[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
    const unsigned char fnd_select[4] = {0x08, 0x04, 0x02, 0x01};
    unsigned char play[4] = {0x73, 0x38, 0x77, 0x6E};
    volatile int currentDigit;
public:
    static FNDController* Instance;
    
private:

public:
    FNDController();
    void SetDisplay(Letter letter);
    void SetDisplay(int num);
    void ShowDisplay();
    void SetAnimation(Animations animation, float speed);
};


#endif