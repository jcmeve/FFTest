// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassTranslator.h"

#include "TESTSimepleMovementSync.generated.h"

UCLASS()
class FFTEST_API UTESTSimepleMovementSync : public UMassTranslator
{
	GENERATED_BODY()
public:
	UTESTSimepleMovementSync();

protected:
	FMassEntityQuery EntityQuery;
	
	virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;
};
