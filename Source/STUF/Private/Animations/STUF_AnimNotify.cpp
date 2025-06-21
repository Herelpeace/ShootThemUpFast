// BGAT studio. All Rights Reserved. 


#include "Animations/STUF_AnimNotify.h"

void USTUF_AnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotified.Broadcast(MeshComp);

	Super::Notify(MeshComp,Animation);
}