// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TESTMassClientBubbleHandler.h"
#include "UObject/Object.h"

/**
 * 
 */
class FFTEST_API UTESTMassSmoothClientBubbleHandler : public FTESTMassClientBubbleHandler
{
protected:
#if UE_REPLICATION_COMPILE_CLIENT_CODE 
	virtual void PostReplicatedChangeEntity(const FMassEntityView& EntityView, const FTESTReplicatedAgent& Item) override;
#endif //UE_REPLICATION_COMPILE_CLIENT_CODE
	
};
