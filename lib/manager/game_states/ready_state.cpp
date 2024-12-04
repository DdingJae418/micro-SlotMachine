#include <fnd_controller.h>
#include <game_enums.h>
#include "ready_state.h"


void ReadyState::StartState()
{
    FNDController* fnd = FNDController::GetInstance();

    // Set 'PLAY' letter and Fade_In_Out' animation at the FND display
    fnd->SetDisplay(Letter::PLAY);
    fnd->SetAnimation(Animation::FADE_IN_OUT, 1);
    fnd->ShowDisplay();
}

void ReadyState::UpdateState()
{

}

void ReadyState::EndState()
{

}