// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassEntityElementTypes.h"
#include "TESTReplicatedAgent.h"
#include "TESTTransformOffset.generated.h"

/**
 * 
 */
USTRUCT()
struct FFTEST_API FTESTTransformOffset : public FMassFragment
{
	GENERATED_BODY()
	
	UPROPERTY(Transient)  
	FReplicatedAgentPositionYawData TransformOffset;  
};




