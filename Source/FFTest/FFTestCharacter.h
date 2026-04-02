// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NavigationData.h"
#include "GameFramework/Character.h"
#include "FFTestCharacter.generated.h"

/**
 *  A controllable top-down perspective character
 */
UCLASS()
class AFFTestCharacter : public ACharacter
{
	GENERATED_BODY()

private:


	
	TArray<FNavPathPoint> Path;
	int32 NextPathPointIndex;
	
	FTimerHandle PathFollowTimerHandle;
	
public:

	/** Constructor */
	AFFTestCharacter();

	/** Initialization */
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void FollowPath();



	void SetFollowingPath(FPathFindingResult PathFindingResult);
	
};

