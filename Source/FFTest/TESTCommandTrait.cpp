// Fill out your copyright notice in the Description page of Project Settings.


#include "TESTCommandTrait.h"

#include "MassEntityTemplateRegistry.h"
#include "TESTOffsetParams.h"


void UTESTCommandTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext,
                                      const UWorld& World) const
{

	BuildContext.AddFragment<FCommandTypeFragment>();
	BuildContext.RequireFragment<FCommandDataFragment>();
	
	FMassEntityManager& EntityManager = UE::Mass::Utils::GetEntityManagerChecked(World);
	
	FCommandDataFragment CommandDataFragment;
	FSharedStruct SharadFragment = EntityManager.GetOrCreateSharedFragment(CommandDataFragment);
	BuildContext.AddSharedFragment(SharadFragment);
	//TODO MOVE 
	FTESTOffsetParams OffsetParamsFragment; 
	const FConstSharedStruct OffsetConstSharedStruct = EntityManager.GetOrCreateConstSharedFragment(OffsetParamsFragment);
	BuildContext.AddConstSharedFragment(OffsetConstSharedStruct);
}

