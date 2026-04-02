// Fill out your copyright notice in the Description page of Project Settings.


#include "TESTSimpleMovementSyncTrait.h"
#include "MassEntityTemplateRegistry.h"
#include "MassActorSubsystem.h"
#include "MassCommonFragments.h"
#include "MassMovementFragments.h"
#include "TESTSimepleMovementSync.h"


void UTESTSimpleMovementSyncTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext,
                                                 const UWorld& World) const
{

	BuildContext.RequireFragment<FTransformFragment>();
	BuildContext.RequireFragment<FMassActorFragment>();
	BuildContext.AddTag<FTESTSimpleMovementSync>();
}
