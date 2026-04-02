// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NavigationData.h"
#include "Subsystems/WorldSubsystem.h"
#include "UnitSubsystem.generated.h"

class AFFTestCharacter;
/**
 * 
 */
UCLASS()
class FFTEST_API UUnitSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
private:
	UPROPERTY()
	TArray<AFFTestCharacter*> Characters;
public:
	void Init(TSubclassOf<AFFTestCharacter> SpawnClass, int32 CharacterNum);
	void MoveTo(FVector Destination);
	FPathFindingResult GetPathPoints(const ACharacter* Character, const FVector& EndPos, UWorld* World);
	void SpawnUnit(TSubclassOf<AFFTestCharacter> SpawnClass, FVector Location);
	
	
};
