// BGAT studio. All Rights Reserved. 


#include "AI/STUF_AICharacter.h"


ASTUF_AICharacter::ASTUF_AICharacter(const FObjectInitializer& ObjInit):Super(ObjInit)
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ASTUF_AICharacter::StaticClass();
}

