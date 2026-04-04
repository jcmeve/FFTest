// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassReplicationTypes.h"
#include "MassReplicationTransformHandlers.h"
#include "TESTReplicatedAgent.generated.h"

/**
 * 
 */
USTRUCT()
struct FFTEST_API FTESTReplicatedAgent : public FReplicatedAgentBase
{
	GENERATED_BODY()
	
	const FReplicatedAgentPositionYawData& GetPositionYawData() const { return PositionYawData; }  
 
	void SetPositionYawData(const FReplicatedAgentPositionYawData& InPositionYawData) { PositionYawData = InPositionYawData; }  
  
private:  
	UPROPERTY(Transient)  
	FReplicatedAgentPositionYawData PositionYawData;
};

