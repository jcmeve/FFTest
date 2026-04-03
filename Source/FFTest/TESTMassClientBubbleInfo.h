// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TESTMassClientBubbleHandler.h"
#include "TESTClientBubbleSerializer.h"
#include "MassClientBubbleInfoBase.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "TESTMassClientBubbleInfo.generated.h"

UCLASS()
class FFTEST_API ATESTMassClientBubbleInfo : public AMassClientBubbleInfoBase
{
	GENERATED_BODY()

	
public:
	ATESTMassClientBubbleInfo(const FObjectInitializer& ObjectInitializer) 
		:Super(ObjectInitializer)
	{
		// Adding our serializer to this array so our parent class can initialize it
		Serializers.Add(&BubbleSerializer);
	}
 
	FTESTClientBubbleSerializer& GetBubbleSerializer() { return BubbleSerializer; }
 
protected:
 
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override 
	{
		Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
		FDoRepLifetimeParams SharedParams;
		SharedParams.bIsPushBased = true;
	
		// Technically, this doesn't need to be PushModel based because it's a FastArray and they ignore it.
		DOREPLIFETIME_WITH_PARAMS_FAST(ATESTMassClientBubbleInfo, BubbleSerializer, SharedParams);
	}
 
protected:
	UPROPERTY(Replicated, Transient) 
	FTESTClientBubbleSerializer BubbleSerializer;
};
