// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassCommonFragments.h"
#include "MassCommonTypes.h"
#include "MassExecutionContext.h"
#include "MassProcessor.h"
#include "TESTOffsetParams.h"
#include "TESTTranslationOffset.h"
#include "TESTSmoothOffsetProcessor.generated.h"

/**
 * 
 */

UCLASS()  
class FFTEST_API UTESTSmoothOffsetProcessor : public UMassProcessor  
{  
	GENERATED_BODY()  
  
public:  
	UTESTSmoothOffsetProcessor()
	{  
		bAutoRegisterWithProcessingPhases = true;  
		ExecutionFlags = static_cast<int32>(EProcessorExecutionFlags::Client);  
		ExecutionOrder.ExecuteAfter.Add(UE::Mass::ProcessorGroupNames::Movement);  
	}
	
	virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override
	{
		EntityQuery.Initialize(EntityManager);
		EntityQuery.AddRequirement<FTESTTranslationOffset>(EMassFragmentAccess::ReadWrite);  
		EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadWrite, EMassFragmentPresence::Optional);  
		EntityQuery.AddConstSharedRequirement<FTESTOffsetParams>();  
		EntityQuery.RegisterWithProcessor(*this);		
	}
  
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override
	{
		EntityQuery.ForEachEntityChunk(Context, [](FMassExecutionContext& Context)  
		{  
			const TArrayView<FTESTTranslationOffset>& TranslationOffsets = Context.GetMutableFragmentView<FTESTTranslationOffset>();  
			const FTESTOffsetParams& Params = Context.GetConstSharedFragment<FTESTOffsetParams>();  
		  
			const float DeltaTime = Context.GetWorld()->DeltaTimeSeconds;  
		  
			for (int32 EntityIndex = 0; EntityIndex < Context.GetNumEntities(); ++EntityIndex)  
			{       
				FTESTTranslationOffset& TranslationOffset = TranslationOffsets[EntityIndex];  
				if (DeltaTime < Params.MaxTimeToSmooth)  
				{          
					TranslationOffset.TranslationOffset *= (1.0f - DeltaTime / Params.SmoothTime);  
				}       
				else  
				{  
					TranslationOffset.TranslationOffset = FVector::ZeroVector;  
				}    
			}
		});
	}
  
private:  
	FMassEntityQuery EntityQuery;  
};

