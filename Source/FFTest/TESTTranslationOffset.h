// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassEntityElementTypes.h"
#include "TESTTranslationOffset.generated.h"

/**
 * 
 */
USTRUCT()
struct FFTEST_API FTESTTranslationOffset : public FMassFragment
{
	GENERATED_BODY()
	
	UPROPERTY(Transient)  
	FVector TranslationOffset = FVector::ZeroVector;  
};




