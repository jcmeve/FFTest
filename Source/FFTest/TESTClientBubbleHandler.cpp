// Fill out your copyright notice in the Description page of Project Settings.


#include "TESTClientBubbleHandler.h"

#include "MassCommonFragments.h"
#if UE_REPLICATION_COMPILE_CLIENT_CODE
void FTESTClientBubbleHandler::PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize)
{
	TArrayView<FTransformFragment> TransformFragments;

	// Add the requirements for the query used to grab all the transform fragments
	auto AddRequirementsForSpawnQuery = [this](FMassEntityQuery& InQuery)
	{
		InQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadWrite);
	};

	// Cache the transform fragments
	auto CacheFragmentViewsForSpawnQuery = [&]
	(FMassExecutionContext& InExecContext)
	{
		TransformFragments = InExecContext.GetMutableFragmentView<FTransformFragment>();
	};

	// Called when a new entity is spawned. Stores the entity location in the transform fragment
	auto SetSpawnedEntityData = [&]
	(const FMassEntityView& EntityView, const FTESTReplicatedAgent& ReplicatedEntity, const int32 EntityIdx)
	{
		TransformFragments[EntityIdx].GetMutableTransform().SetLocation(ReplicatedEntity.GetEntityLocation());
	};

	auto SetModifiedEntityData = [this](const FMassEntityView& EntityView, const FTESTReplicatedAgent& Item)
	{
		PostReplicatedChangeEntity(EntityView, Item);
	};

	PostReplicatedAddHelper(AddedIndices, AddRequirementsForSpawnQuery, CacheFragmentViewsForSpawnQuery, SetSpawnedEntityData, SetModifiedEntityData);

}

void FTESTClientBubbleHandler::PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize)
{
	PostReplicatedChangeHelper(
		ChangedIndices,
		[this](const FMassEntityView& EntityView, const FTESTReplicatedAgent& Item)
		{
			PostReplicatedChangeEntity(EntityView, Item);
		});
}

void FTESTClientBubbleHandler::PostReplicatedChangeEntity(const FMassEntityView& EntityView,
                                                          const FTESTReplicatedAgent& Item)
{
	// Grabs the transform fragment from the entity  
	FTransformFragment& TransformFragment = EntityView.GetFragmentData<FTransformFragment>();

	// Sets the transform location with the agent location  
	TransformFragment.GetMutableTransform().SetLocation(Item.GetEntityLocation());
}

#endif //UE_REPLICATION_COMPILE_CLIENT_CODE
