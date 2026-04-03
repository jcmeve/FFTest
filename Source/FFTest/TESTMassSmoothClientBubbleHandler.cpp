// Fill out your copyright notice in the Description page of Project Settings.


#include "TESTMassSmoothClientBubbleHandler.h"

#include "TESTOffsetParams.h"
#include "TESTTranslationOffset.h"

#if UE_REPLICATION_COMPILE_CLIENT_CODE  
void UTESTMassSmoothClientBubbleHandler::PostReplicatedChangeEntity(const FMassEntityView& EntityView,
                                                                    const FTESTReplicatedAgent& Item)
{
	FTransformFragment& TransformFragment = EntityView.GetFragmentData<FTransformFragment>();
  	
	const FVector PreviousLocation = TransformFragment.GetTransform().GetLocation();
	FTESTMassClientBubbleHandler::PostReplicatedChangeEntity(EntityView, Item);
	const FVector NewLocation = TransformFragment.GetTransform().GetLocation();
  
 
	// Initializes mesh offset 
	FTESTTranslationOffset& TranslationOffset = EntityView.GetFragmentData<FTESTTranslationOffset>();
	const FTESTOffsetParams& OffsetParams = EntityView.GetConstSharedFragmentData<FTESTOffsetParams>();
  	
	if (OffsetParams.MaxSmoothNetUpdateDistanceSqr > FVector::DistSquared(PreviousLocation, NewLocation))
	{
		// Offsetting the mesh to sync with the sever locations smoothly
		TranslationOffset.TranslationOffset += PreviousLocation - NewLocation;
	}
}
#endif //UE_REPLICATION_COMPILE_CLIENT_CODE  