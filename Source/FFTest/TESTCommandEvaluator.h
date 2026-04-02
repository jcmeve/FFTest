// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassStateTreeTypes.h"
#include "TESTCommandTrait.h"
#include "UObject/Object.h"
#include "TESTCommandEvaluator.generated.h"

USTRUCT()
struct FTESTCommandEvaluatorInstanceData
{
	GENERATED_BODY()

	// StateTree 에디터에서 보게 될 출력 값
	UPROPERTY(EditAnywhere, Category = "Output")
	ECommandType CurrentCommand = ECommandType::None;
};

/**
 * 
 */
USTRUCT()
struct FFTEST_API FTESTCommandEvaluator : public FMassStateTreeEvaluatorBase
{
	GENERATED_BODY()
	using FInstanceDataType = FTESTCommandEvaluatorInstanceData;
protected:
	// 사용할 데이터 핸들 (스키마 허용을 위해 필요)
	TStateTreeExternalDataHandle<FCommandTypeFragment> CommandTypeHandle;

	virtual bool Link(FStateTreeLinker& Linker) override;
	virtual void Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;
    
	// 이 Evaluator가 사용하는 데이터 구조체 지정
	virtual const UScriptStruct* GetInstanceDataType() const override { return FTESTCommandEvaluatorInstanceData::StaticStruct(); }
};
