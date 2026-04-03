// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "TESTSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class FFTEST_API UTESTSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	virtual void PostInitialize() override;
};
