// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitSubsystem.h"

#include "AITypes.h"
#include "FFTestCharacter.h"
#include "NavigationSystem.h"
#include "GameFramework/PawnMovementComponent.h"
#include "NavFilters/NavigationQueryFilter.h"
#include "Navigation/PathFollowingComponent.h"


void UUnitSubsystem::Init(TSubclassOf<AFFTestCharacter> SpawnClass, int32 CharacterNum)
{
	
	for (int32 i = 0; i < CharacterNum; i++)
	{
		SpawnUnit(SpawnClass, FVector(200*(i/10)-1000,200*(i%10)-1000,1000+i*100.0));
	}
	
}

void UUnitSubsystem::MoveTo(FVector Destination)
{
	for (auto actor : Characters)
	{
		if (IsValid(actor)  == false ) continue;
		auto Ret = GetPathPoints(actor, Destination, GetWorld());
		
		actor->SetFollowingPath(Ret);
	}
}


FPathFindingResult UUnitSubsystem::GetPathPoints(const ACharacter* Character, const FVector& EndPos, UWorld* World)
{
	FPathFindingQuery Query;
	
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	const ANavigationData* NavData = (NavSys == nullptr) ? nullptr : NavSys->GetNavDataForProps(Character->GetMovementComponent()->GetNavAgentPropertiesRef(), Character->GetActorLocation()) ;

	if (NavData)
	{
		FVector GoalLocation = EndPos;
		TSubclassOf<UNavigationQueryFilter> FilterClass = UNavigationQueryFilter::StaticClass();
		FSharedConstNavQueryFilter NavFilter = UNavigationQueryFilter::GetQueryFilter(*NavData, this, FilterClass);
		Query = FPathFindingQuery(Character, *NavData, Character->GetActorLocation(), GoalLocation, NavFilter);
		Query.SetAllowPartialPaths(true);
		Query.SetRequireNavigableEndLocation(true);
		
	}
	
	// (선택) 특정 액터를 위한 경로 탐색일 경우 Owner를 지정할 수 있습니다.
	// Query.Owner = MyActor; 

	// 3. 동기적 경로 탐색 호출
	// EPathFindingMode::Regular가 기본값으로 적용됩니다.
	FPathFindingResult PathResult = NavSys->FindPathSync(Query);

	return PathResult;
}

void UUnitSubsystem::SpawnUnit(TSubclassOf<AFFTestCharacter> SpawnClass, FVector Location)
{
	AFFTestCharacter* Unit = GetWorld()->SpawnActor<AFFTestCharacter>(SpawnClass, Location, FRotator::ZeroRotator);
	if (Unit){
		UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
		if (!NavSys) return;

		FNavLocation ResultLocation;
		// 현재 위치를 기준으로 반경 500 내의 바닥을 찾음
		if (NavSys->ProjectPointToNavigation(Unit->GetActorLocation(), ResultLocation, FVector(500.f, 500.f, 50000.f)))
		{
			Unit->SetActorLocation(ResultLocation.Location);
		}
		Characters.Add(Unit);
	}
}

