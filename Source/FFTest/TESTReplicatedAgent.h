// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassReplicationTypes.h"
#include "TESTReplicatedAgent.generated.h"

/**
 * 
 */
USTRUCT()
struct FFTEST_API FTESTReplicatedAgent : public FReplicatedAgentBase
{
	GENERATED_BODY()
	
	const FVector& GetEntityLocation() const { return EntityLocation; }  
 
	void SetEntityLocation(const FVector& InEntityLocation) { EntityLocation = InEntityLocation; }  
  
private:  
	UPROPERTY(Transient)  
	FVector_NetQuantize EntityLocation;  
};

