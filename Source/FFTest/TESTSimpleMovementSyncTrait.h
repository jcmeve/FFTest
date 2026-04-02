// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassEntityTraitBase.h"
#include "MassEntityTypes.h"
#include "TESTSimpleMovementSyncTrait.generated.h"

USTRUCT()
struct FTESTSimpleMovementSync : public FMassTag
{
	GENERATED_BODY()
	
};
 

UCLASS()
class FFTEST_API UTESTSimpleMovementSyncTrait : public UMassEntityTraitBase
{
	GENERATED_BODY()

protected:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;
};
