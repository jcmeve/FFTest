// Fill out your copyright notice in the Description page of Project Settings.


#include "TESTSubsystem.h"

#include "MassReplicationSubsystem.h"
#include "TESTMassClientBubbleInfo.h"
#include "TESTMassSmoothClientBubbleSmoothInfo.h"

void UTESTSubsystem::PostInitialize()
{
	Super::PostInitialize();
	const UWorld* World = GetWorld();  
	UMassReplicationSubsystem* ReplicationSubsystem = UWorld::GetSubsystem<UMassReplicationSubsystem>(World);
	ReplicationSubsystem->RegisterBubbleInfoClass(ATESTMassClientBubbleInfo::StaticClass());
	ReplicationSubsystem->RegisterBubbleInfoClass(ATESTMassSmoothClientBubbleSmoothInfo::StaticClass());
}
