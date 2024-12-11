#ifndef SWITCH_CONTROLLER_H
#define SWITCH_CONTROLLER_H

#include <game_manager.h>

using game_enums::Switch;

class SwitchController : public UpdateListener
{
private:
    static SwitchController* instance;
    volatile bool isSwitchOneClicked;
    volatile bool isSwitchTwoClicked;
private:
    SwitchController();
    ~SwitchController() = default;
    SwitchController(const SwitchController&) = delete;
    SwitchController& operator= (const SwitchController&) = delete;
public:
    static SwitchController& GetInstance();
    static void DestroyInstance();
    void OnSwitchClick(Switch sw);
    void Update() override;
};

#endif