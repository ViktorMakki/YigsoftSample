// Copyright Epic Games, Inc. All Rights Reserved.

#include "YigsoftSampleGameMode.h"
#include "YigsoftSampleCharacter.h"
#include "UObject/ConstructorHelpers.h"

AYigsoftSampleGameMode::AYigsoftSampleGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
