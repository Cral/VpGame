// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
// 
#include "VpGame.h"
#include "VpGameMode.h"
#include "VpPawn.h"

AVpGameMode::AVpGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AVpPawn::StaticClass();
}

