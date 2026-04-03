// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassClientBubbleHandler.h"
#include "TESTReplicatedAgent.h"
#include "TESTMassFastArrayItem.generated.h"

/**
 * 
 */
USTRUCT()
struct FFTEST_API FTESTMassFastArrayItem : public FMassFastArrayItemBase
{
	GENERATED_BODY()
	
	FTESTMassFastArrayItem() = default;  
	FTESTMassFastArrayItem(const FTESTReplicatedAgent& InAgent, const FMassReplicatedAgentHandle InHandle)  
		: FMassFastArrayItemBase(InHandle), Agent(InAgent) {}  
    
	/** This typedef is required to be provided in FMassFastArrayItemBase derived classes (with the associated FReplicatedAgentBase derived class) */  
	typedef FTESTReplicatedAgent FReplicatedAgentType;  
    
	UPROPERTY()  
	FTESTReplicatedAgent Agent;  
};
