// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassClientBubbleInfoBase.h"
#include "TESTMassSmoothClientBubbleSerializer.h"
#include "Net/UnrealNetwork.h"
#include "TESTMassSmoothClientBubbleSmoothInfo.generated.h"

UCLASS()
class FFTEST_API ATESTMassSmoothClientBubbleSmoothInfo : public AMassClientBubbleInfoBase
{
	GENERATED_BODY()
  
public:
	ATESTMassSmoothClientBubbleSmoothInfo(const FObjectInitializer& ObjectInitializer)
		: AMassClientBubbleInfoBase(ObjectInitializer)
	{
		Serializers.Add(&BubbleSerializer);
		SetNetUpdateFrequency(100);
	}
 
	FTESTMassSmoothClientBubbleSerializer& GetBubbleSerializer() { return BubbleSerializer; }
 
protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override
	{
		Super::GetLifetimeReplicatedProps(OutLifetimeProps);
  
		FDoRepLifetimeParams SharedParams;
		SharedParams.bIsPushBased = true;
  
		// Technically, this doesn't need to be PushModel based because it's a FastArray and they ignore it.
		DOREPLIFETIME_WITH_PARAMS_FAST(ATESTMassSmoothClientBubbleSmoothInfo, BubbleSerializer, SharedParams);
	}
 
private:
	/** Contains the entities fast array */
	UPROPERTY(Replicated, Transient) 
	FTESTMassSmoothClientBubbleSerializer BubbleSerializer;
};
