// Fill out your copyright notice in the Description page of Project Settings.


#include "TESTMassSmoothClientBubbleHandler.h"

#include "TESTOffsetParams.h"
#include "TESTTransformOffset.h"

#if UE_REPLICATION_COMPILE_CLIENT_CODE  
void UTESTMassSmoothClientBubbleHandler::PostReplicatedChangeEntity(const FMassEntityView& EntityView,
                                                                    const FTESTReplicatedAgent& Item)
{
	FTransformFragment& TransformFragment = EntityView.GetFragmentData<FTransformFragment>();
  	
	const FVector PreviousLocation = TransformFragment.GetTransform().GetLocation();
	const float PreviousYaw = FRotator::NormalizeAxis(TransformFragment.GetTransform().Rotator().Yaw);
	FTESTMassClientBubbleHandler::PostReplicatedChangeEntity(EntityView, Item);
	const FVector NewLocation = TransformFragment.GetTransform().GetLocation();
	const float NewYaw = FRotator::NormalizeAxis(TransformFragment.GetTransform().Rotator().Yaw);
  
 
	// Initializes mesh offset 
	FTESTTransformOffset& TranslationOffset = EntityView.GetFragmentData<FTESTTransformOffset>();
	const FTESTOffsetParams& OffsetParams = EntityView.GetConstSharedFragmentData<FTESTOffsetParams>();
  	
	if (OffsetParams.MaxSmoothNetUpdateDistanceSqr > FVector::DistSquared(PreviousLocation, NewLocation))
	{
		// Offsetting the mesh to sync with the sever locations smoothly
		TranslationOffset.TransformOffset.SetPosition( TranslationOffset.TransformOffset.GetPosition()+ PreviousLocation - NewLocation);
	}
	
	const float DeltaYaw = FMath::FindDeltaAngleDegrees(NewYaw, PreviousYaw);
	if (OffsetParams.MaxSmoothNetUpdateYaw > FMath::Abs(DeltaYaw))
	{
		// 기존 오프셋에 최단 거리 각도 차이를 더해줌
		float CurrentYawOffset = TranslationOffset.TransformOffset.GetYaw();
		TranslationOffset.TransformOffset.SetYaw(FRotator::NormalizeAxis(CurrentYawOffset + DeltaYaw));
	}
	
}
#endif //UE_REPLICATION_COMPILE_CLIENT_CODE  