#include "UnistrokeTemplate.h"

FUnistrokeTemplate::FUnistrokeTemplate()
{
	Name = "";
	Vector = TArray<float>();
	Points = TArray<FUnistrokePoint>();
}

FUnistrokeTemplate::FUnistrokeTemplate(const FString &Name, const TArray<FUnistrokePoint> &Points)
{
	this->Name = Name;
	this->Points = Points;

	FUnistrokePoint::Resample(this->Points, NumPoints);

	float Radians = FUnistrokePoint::IndicativeAngle(Points);

	FUnistrokePoint::RotateBy(this->Points, -Radians);

	FUnistrokePoint::ScaleTo(this->Points, SquareSize);

	FUnistrokePoint::TranslateTo(this->Points, FUnistrokePoint());

	this->Vector = FUnistrokePoint::Vectorize(this->Points);
}

FUnistrokeTemplate::~FUnistrokeTemplate()
{
}
