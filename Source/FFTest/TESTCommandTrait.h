// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassEntityElementTypes.h"
#include "MassEntityHandle.h"
#include "MassEntityTraitBase.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "StructUtils/SharedStruct.h"
#include "TESTCommandTrait.generated.h"

/**
 * 
 */
UENUM()
enum class ECommandType:uint8
{
	None,
	MoveToLocation,
};


USTRUCT()
struct FCommandTypeFragment : public FMassFragment
{
	GENERATED_BODY()

	FCommandTypeFragment() = default;

	FCommandTypeFragment(const ECommandType InType)
		: Type(InType)
	{
	}

	ECommandType GetType() const { return Type; }
	void SetType(const ECommandType InType) { Type = InType; }

protected:
	UPROPERTY(Transient)
	ECommandType Type;
};

USTRUCT()
struct FCommandDataFragment : public FMassSharedFragment
{
	GENERATED_BODY()
	FCommandDataFragment() = default;

	FCommandDataFragment(const FVector& InLocation, const FMassEntityHandle& InTarget)
		: Location(InLocation),
		  Target(InTarget)
	{
	}

	FVector GetLocation() const { return Location; }
	void SetLocation(const FVector& InLocation) { Location = InLocation; }

	FMassEntityHandle GetTarget() const { return Target; }
	void SetTarget(const FMassEntityHandle& InTarget) { Target = InTarget; }

protected:
	UPROPERTY(Transient)
	FVector Location;
	UPROPERTY(Transient)
	FMassEntityHandle Target;
};

UCLASS()
class FFTEST_API UTESTCommandTrait : public UMassEntityTraitBase
{
	GENERATED_BODY()

protected:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;
};
