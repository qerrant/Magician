#pragma once

#include "CoreMinimal.h"
#include "UnistrokePoint.h"
#include "UnistrokeTemplate.generated.h"

static const int NumPoints = 64;
static const float SquareSize = 250.0f;

USTRUCT()
struct MAGICIAN_API FUnistrokeTemplate
{
	GENERATED_USTRUCT_BODY()

public:
	FUnistrokeTemplate();
	FUnistrokeTemplate(const FString &Name, const TArray<FUnistrokePoint> &Points);
	~FUnistrokeTemplate();

public:
	FString Name;
	TArray<float> Vector;
	TArray<FUnistrokePoint> Points;
};
