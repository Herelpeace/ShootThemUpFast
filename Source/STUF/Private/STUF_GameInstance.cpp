// BGAT studio. All Rights Reserved. 


#include "STUF_GameInstance.h"
#include "Sound/STUF_SoundFuncLib.h"

void USTUF_GameInstance::ToggleVolume()
{
	USTUF_SoundFuncLib::ToggleSoundClassVolume(MasterSoundClass);


}