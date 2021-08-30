#pragma once

#include "CoreMinimal.h"
#include "UnistrokeRectangle.h"
#include "UnistrokePoint.generated.h"

static const float Phi = 0.5f * (-1.0f + FMath::Sqrt(5.0f));

USTRUCT()
struct MAGICIAN_API FUnistrokePoint
{
	GENERATED_USTRUCT_BODY()

public:
	FUnistrokePoint();
	FUnistrokePoint(const float &X, const float &Y);
	~FUnistrokePoint();
	static const TArray<FUnistrokePoint> Convert(const TArray<FVector2D> &Points);
	static void Resample(TArray<FUnistrokePoint> &Points, const int &Num);
	static const float PathLength(const TArray<FUnistrokePoint> &Points);
	static const float Distance(const FUnistrokePoint &PointA, const FUnistrokePoint &PointB);
	static const float IndicativeAngle(const TArray<FUnistrokePoint> &Points);
	static const FUnistrokePoint Centroid(const TArray<FUnistrokePoint> &Points);
	static void RotateBy(TArray<FUnistrokePoint> &Points, const float &Radians);
	static void ScaleTo(TArray<FUnistrokePoint> &Points, const float &Size);
	static const FUnistrokeRectangle BoundingRect(const TArray<FUnistrokePoint> &Points);
	static void TranslateTo(TArray<FUnistrokePoint> &Points, const FUnistrokePoint &Point);
	static const TArray<float> Vectorize(const TArray<FUnistrokePoint> &Points);
	static const float OptimalCosineDistance(const TArray<float> &VectorA, const TArray<float> &VectorB);
	static const float DistanceAtBestAngle(const TArray<FUnistrokePoint> &Points, const TArray<FUnistrokePoint> &TemplatePoints, const float &FromAngle, const float &ToAngle, const float &Threshold);
	static const float DistanceAtAngle(const TArray<FUnistrokePoint> &Points, const TArray<FUnistrokePoint> &TemplatePoints, const float &Radians);
	static const float PathDistance(const TArray<FUnistrokePoint> &PathA, const TArray<FUnistrokePoint> &PathB);
	static void GSS(const float& a, const float& b, const TArray<FUnistrokePoint>& Points, const TArray<FUnistrokePoint>& TemplatePoints, float& x, float& f);

public:
	float X;
	float Y;
};
