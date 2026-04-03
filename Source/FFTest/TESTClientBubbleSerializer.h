// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassClientBubbleSerializerBase.h"
#include "TESTClientBubbleHandler.h"
#include "TESTMassFastArrayItem.h"
#include "TESTClientBubbleSerializer.generated.h"

/**
 * 
 */
USTRUCT()
struct FFTEST_API FTESTClientBubbleSerializer : public FMassClientBubbleSerializerBase
{
	GENERATED_BODY()
public:
	FTESTClientBubbleSerializer()
	{
		Bubble.Initialize(Entities, *this);
	}
 
	/** Define a custom replication for this struct */
	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParams)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FTESTMassFastArrayItem, FTESTClientBubbleSerializer>(Entities, DeltaParams, *this);
	}
 
	/** The one responsible for storing the server data in the client fragments */
	FTESTClientBubbleHandler Bubble;
 
protected:
	/** Fast Array of Agents for efficient replication. Maintained as a freelist on the server, to keep index consistency as indexes are used as Handles into the Array 
	 *  Note array order is not guaranteed between server and client so handles will not be consistent between them, FMassNetworkID will be.
	 */
	UPROPERTY(Transient)
	TArray<FTESTMassFastArrayItem> Entities;
	
};

template<>
struct TStructOpsTypeTraits<FTESTClientBubbleSerializer> : public TStructOpsTypeTraitsBase2<FTESTClientBubbleSerializer>
{
	enum
	{
		// We need to use the NetDeltaSerialize function for this struct to define a custom replication
		WithNetDeltaSerializer = true,
 
		// Copy is not allowed for this struct
		WithCopy = false,
	};
};
