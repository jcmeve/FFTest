// Copyright Epic Games, Inc. All Rights Reserved.

#include "FFTestCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "NavFilters/NavigationQueryFilter.h"
#include "Navigation/PathFollowingComponent.h"

AFFTestCharacter::AFFTestCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void AFFTestCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
	{
		// 움직일 대상을 캡슐 컴포넌트로 명시적 지정
		MoveComp->SetUpdatedComponent(GetCapsuleComponent());
	}
	// stub
}

void AFFTestCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorldTimerManager().ClearTimer(PathFollowTimerHandle);
}

void AFFTestCharacter::FollowPath()
{
	if (Path.Num() > 0 && Path.IsValidIndex(NextPathPointIndex))
	{
		FVector CurrentLocation = GetActorLocation();
		FVector TargetLocation = Path[NextPathPointIndex].Location;
		FVector Direction = (TargetLocation - CurrentLocation);
		Direction.Z = 0.0f;
	
		if (Direction.Size2D() < 50.0f)
		{
			NextPathPointIndex++;
			return;
		}
	
		FVector WorldDirection = Direction.GetSafeNormal();
		AddMovementInput(WorldDirection);
	}else
	{
		GetWorldTimerManager().ClearTimer(PathFollowTimerHandle);
	}
}


void AFFTestCharacter::SetFollowingPath(FPathFindingResult PathFindingResult)
{
	NextPathPointIndex = 0;
	Path = PathFindingResult.Path->GetPathPoints();
	GetWorldTimerManager().SetTimer(PathFollowTimerHandle, this, &ThisClass::FollowPath, 0.02, true);
	
}
