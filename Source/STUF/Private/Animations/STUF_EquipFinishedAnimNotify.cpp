// BGAT studio. All Rights Reserved. 


#include "Animations/STUF_EquipFinishedAnimNotify.h"

void USTUF_EquipFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotified.Broadcast(MeshComp);

	Super::Notify(MeshComp,Animation);
}