#include "UnistrokeRecognizer.h"

FUnistrokeRecognizer::FUnistrokeRecognizer()
{
}

FUnistrokeRecognizer::~FUnistrokeRecognizer()
{
}

FUnistrokeResult FUnistrokeRecognizer::Recognize(const TArray<FVector2D> &VectorPoints, const bool &UseProtractor)
{
	TArray<FUnistrokePoint> Points = FUnistrokePoint::Convert(VectorPoints);

	if (Points.Num() < 2 || FUnistrokePoint::PathLength(Points) < 100.0f) return FUnistrokeResult("Too few points made", 0.0, 0.0);

	const FUnistrokeTemplate Candidate = FUnistrokeTemplate("", Points);

	int TemplateIndex = -1;
	float BestDistance = TNumericLimits<float>::Max();

	const FDateTime StartTime = FDateTime::Now();
	
	for (int i = 0; i < Templates.Num(); i++)
	{

		const float distance = UseProtractor ? FUnistrokePoint::OptimalCosineDistance(Templates[i].Vector, Candidate.Vector) :
			FUnistrokePoint::DistanceAtBestAngle(Candidate.Points, Templates[i].Points, -AngleRange, AngleRange, AnglePrecision);

		if (distance < BestDistance)
		{
			BestDistance = distance;
			TemplateIndex = i;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Tested"));

	const FDateTime EndTime = FDateTime::Now();
	const float ElapsedTime = (EndTime.GetMillisecond() - StartTime.GetMillisecond()) / 1000;
	const float Score = UseProtractor ? (1.0 - BestDistance) : (1.0 - BestDistance / HalfDiagonal);

	return (TemplateIndex == -1) ? FUnistrokeResult("No match", 0.0, ElapsedTime) : FUnistrokeResult(Templates[TemplateIndex].Name, Score, ElapsedTime);
}

void FUnistrokeRecognizer::AddTemplate(const FString &Name, const TArray<FVector2D> &VectorPoints)
{
	TArray<FUnistrokePoint> Points = FUnistrokePoint::Convert(VectorPoints);

	Templates.Add(FUnistrokeTemplate(Name, Points));
}

void FUnistrokeRecognizer::Reset()
{
	Templates.SetNum(NumTemplates);
}
