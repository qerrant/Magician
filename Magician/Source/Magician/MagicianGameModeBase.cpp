#include "MagicianGameModeBase.h"

AMagicianGameModeBase::AMagicianGameModeBase()
{
	PlayerControllerClass = AMagicianPlayerController::StaticClass();
	DefaultPawnClass = AMagicianPawn::StaticClass();
}
