#ifndef BUZZER_CONTROLLER_H
#define BUZZER_CONTROLLER_H

#include <fixed_rate_updater.h>
#include <map>
#include <game_enums.h>

using game_enums::Sound;

class BuzzerSound;


class BuzzerController : public UpdateListener
{
private:
    static BuzzerController* instance;
    std::map<Sound, BuzzerSound*> buzzerSoundMap;
    BuzzerSound* currentSound;
    float playTime;
private:
    BuzzerController() : playTime(0) {};
    void PlayNote(uint16_t frequency);
public:
    static BuzzerController* GetInstance();
    void Update() override;
    void StartSound(Sound Sound, bool loop = false);
    bool IsSoundPlaying();
};

#endif