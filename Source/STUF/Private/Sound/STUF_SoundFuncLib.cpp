// BGAT studio. All Rights Reserved. 


#include "Sound/STUF_SoundFuncLib.h"
#include "Sound/SoundClass.h"
#include "Logging/StructuredLog.h"

DEFINE_LOG_CATEGORY_STATIC (LogSTUFSoundFuncLib, All, All);


void USTUF_SoundFuncLib::SetSoundClassVolume(USoundClass* SoundClass, float Volume)
{
	if(!SoundClass) return;

	SoundClass->Properties.Volume = FMath::Clamp(Volume, 0.0f, 1.0f);

	UE_LOGFMT(LogSTUFSoundFuncLib, Warning,"Sound class volume was changed: {0} = {1} ", *SoundClass->GetName(), SoundClass->Properties.Volume);

}


void USTUF_SoundFuncLib::ToggleSoundClassVolume(USoundClass* SoundClass)
{
	if(!SoundClass) return;

	const auto NextVolume = SoundClass->Properties.Volume > 0.0f ? 0.0f : 1.0f;

	SetSoundClassVolume(SoundClass,NextVolume);

}


