#include <ready_state.h>
#include <fnd_controller.h>
#include <game_enums.h>

using game_enums::Letter;


ReadyState::ReadyState(GameManager gm) : gameManager(gm) { }

void ReadyState::StartState()
{
    // set 'PLAY' letter at the FND display
    FNDController::Instance->SetDisplay(Letter::PLAY);
}

void ReadyState::UpdateState()
{

}

void ReadyState::EndState()
{

}