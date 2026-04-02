// Fill out your copyright notice in the Description page of Project Settings.


#include "TESTCommandEvaluator.h"

#include "StateTreeExecutionContext.h"
#include "StateTreeLinker.h"

bool FTESTCommandEvaluator::Link(FStateTreeLinker& Linker)
{
	// 스키마 에러를 방지하기 위해 데이터를 링크합니다.
	Linker.LinkExternalData(CommandTypeHandle);
	return true;
}

void FTESTCommandEvaluator::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
	FInstanceDataType& InstanceData =  Context.GetInstanceData(*this);
    
	const FCommandTypeFragment& CommandType = Context.GetExternalData(CommandTypeHandle);
    
	InstanceData.CurrentCommand = CommandType.GetType();
	
}