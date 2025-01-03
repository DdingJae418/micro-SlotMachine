#ifndef BUZZER_CONTROLLER_H
#define BUZZER_CONTROLLER_H

#include <fixed_rate_updater.h>
#include <map>
#include <game_enums.h>
#include <sounds.h>

class BuzzerController : public UpdateListener
{
private:
    static BuzzerController* instance;
    const BuzzerSound* currentSound;
    NoteIter currentNote;
    float playSpeed;
    bool loopSound;
    float playTime;
    bool isMute;
private:
    BuzzerController();
    ~BuzzerController() = default;
    BuzzerController(const BuzzerController&) = delete;
    BuzzerController& operator=(const BuzzerController&) = delete;
    void PlayNote(double frequency);
public:
    static BuzzerController& GetInstance();
    static void DestroyInstance();
    void StartSound(const BuzzerSound* sound, float speed = 1, bool loop = false);
    void Update() override;
    bool IsSoundPlaying();
    void MuteBuzzer(bool value);
};

#endif