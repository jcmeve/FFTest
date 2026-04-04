// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassEntityElementTypes.h"
#include "TESTOffsetParams.generated.h"

/**
 * 
 */
USTRUCT()  
struct FFTEST_API FTESTOffsetParams : public FMassConstSharedFragment  
{  
	GENERATED_BODY()  
 
	/** Maximum time the smoothing can take. If it takes more than this values it will snap to the actual position */  
	UPROPERTY(EditAnywhere, meta = (UIMin = 0.0f, ClampMin = 0.0f))  
	float MaxTimeToSmooth = 1.0f;  
 
	/** How much time the smooth can take */  
	UPROPERTY(EditAnywhere, meta = (UIMin = 0.0f, ClampMin = 0.0f))  
	float SmoothTime = 0.05f;  
//	float SmoothTime = 0.2f;  
 
	/** The tolerated distance to smooth. If the distance is higher the mesh will snap to the actual position. */  
	UPROPERTY(EditAnywhere, meta = (UIMin = 0.0f, ClampMin = 0.0f))  
	float MaxSmoothNetUpdateDistance = 50.0f;  
 
	float MaxSmoothNetUpdateDistanceSqr = 2500.0f;  
	
	UPROPERTY(EditAnywhere, meta = (UIMin = 0.0f, ClampMin = 0.0f))  
	float MaxSmoothNetUpdateYaw = 180.0f;  
 
 
public:  
	/** Returns a copy of this instance with the parameters validated */
	FTESTOffsetParams GetValidated() const
	{  
		FTESTOffsetParams Params = *this;  
		Params.MaxTimeToSmooth = FMath::Max(0.0f, Params.MaxTimeToSmooth);  
		Params.SmoothTime = FMath::Max(0.0f, Params.SmoothTime);  
		Params.MaxSmoothNetUpdateDistance = FMath::Max(0.0f, Params.MaxSmoothNetUpdateDistance);  
		Params.MaxSmoothNetUpdateDistanceSqr = Params.MaxSmoothNetUpdateDistance * Params.MaxSmoothNetUpdateDistance;  
		return Params;  
	}
};