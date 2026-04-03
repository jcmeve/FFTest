// Fill out your copyright notice in the Description page of Project Settings.
#include "TESTSimepleMovementSync.h"

#include "TESTSimpleMovementSyncTrait.h"
#include "MassCommonFragments.h"
#include "MassCommonTypes.h"
#include "MassExecutionContext.h"
#include "MassEntityManager.h"
#include "GameFramework/Actor.h"
#include "MassActorSubsystem.h"
#include "TESTTranslationOffset.h"

UTESTSimepleMovementSync::UTESTSimepleMovementSync()
	: EntityQuery(*this)
{
	ExecutionFlags = (int32)EProcessorExecutionFlags::AllNetModes;
	ExecutionOrder.ExecuteInGroup = UE::Mass::ProcessorGroupNames::UpdateWorldFromMass;
	ExecutionOrder.ExecuteAfter.Add(UE::Mass::ProcessorGroupNames::Movement);
	RequiredTags.Add<FTESTSimpleMovementSync>();
	bRequiresGameThreadExecution = true;
}

void UTESTSimepleMovementSync::ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager)
{
	AddRequiredTagsToQuery(EntityQuery);
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadOnly);
	EntityQuery.AddRequirement<FMassActorFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddRequirement<FTESTTranslationOffset>(EMassFragmentAccess::ReadWrite);
}

void UTESTSimepleMovementSync::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	// EntityQuery.ForEachEntityChunk(Context, [this](FMassExecutionContext& Context)
	// {	
	// 	const TArrayView<FMassActorFragment> ActorList = Context.GetMutableFragmentView<FMassActorFragment>();
	// 	const TConstArrayView<FTransformFragment> TransformList = Context.GetFragmentView<FTransformFragment>();
	// 	const int32 NumEntities = Context.GetNumEntities();
	// 	for (int32 i = 0; i < NumEntities; ++i)
	// 	{
	// 		if (AActor* Actor = ActorList[i].GetMutable())
	// 		{
	// 			Actor->SetActorTransform(TransformList[i].GetTransform(), false, nullptr, ETeleportType::TeleportPhysics);
	// 		}
	// 	}
	// });
	
	EntityQuery.ForEachEntityChunk(Context, [](FMassExecutionContext& Context)
  	{
  		const TConstArrayView<FTransformFragment> TransformList = Context.GetFragmentView<FTransformFragment>();
  		const TConstArrayView<FTESTTranslationOffset> MeshOffsetList = Context.GetFragmentView<FTESTTranslationOffset>();
		const TArrayView<FMassActorFragment> ActorList = Context.GetMutableFragmentView<FMassActorFragment>();
  
  		for (int32 EntityIdx = 0; EntityIdx < Context.GetNumEntities(); EntityIdx++)
  		{
  			const FTransformFragment& TransformFragment = TransformList[EntityIdx];
  
  			FVector MeshTranslationOffset = FVector::ZeroVector;
  			if (MeshOffsetList.Num() > 0)
  			{
  				MeshTranslationOffset = MeshOffsetList[EntityIdx].TranslationOffset;
  			}
  
  			FTransform Transform = TransformFragment.GetTransform();
  			Transform.SetLocation(Transform.GetLocation() + MeshTranslationOffset);
		    if (AActor* Actor = ActorList[EntityIdx].GetMutable())
		    {
			    Actor->SetActorTransform(Transform, false, nullptr,
			                             ETeleportType::TeleportPhysics);
		    }
  		}
  	});
	
	
	
	
}