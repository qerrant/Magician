#include "UnistrokePoint.h"

FUnistrokePoint::FUnistrokePoint()
{
	X = 0.0f;
	Y = 0.0f;
}

FUnistrokePoint::FUnistrokePoint(const float &X, const float &Y)
{
	this->X = X;
	this->Y = Y;
}

const TArray<FUnistrokePoint> FUnistrokePoint::Convert(const TArray<FVector2D> &Points)
{
	TArray<FUnistrokePoint> NewPoints;

	for (const FVector2D &Point : Points)
	{
		NewPoints.Add(FUnistrokePoint(Point.X, Point.Y));
	}

	return NewPoints;
}

void FUnistrokePoint::Resample(TArray<FUnistrokePoint> &Points, const int &Num)
{
	const float IntervalLength = PathLength(Points) / (Num - 1);
	float D = 0.0f;
	TArray<FUnistrokePoint> OldPoints = Points;

	Points.SetNum(1);

	for (int i = 1; i < OldPoints.Num(); ++i)
	{
		const float d = Distance(OldPoints[i - 1], OldPoints[i]);

		if ((D + d) >= IntervalLength)
		{
			const float qx = OldPoints[i - 1].X + ((IntervalLength - D) / d) * (OldPoints[i].X - OldPoints[i - 1].X);
			const float qy = OldPoints[i - 1].Y + ((IntervalLength - D) / d) * (OldPoints[i].Y - OldPoints[i - 1].Y);
			FUnistrokePoint NewPoint = FUnistrokePoint(qx, qy);

			Points.Add(NewPoint);
			OldPoints.Insert(NewPoint, i);

			D = 0.0f;
		} else D += d;
	}

	if (Points.Num() == (Num - 1))
	{
		Points.Add(OldPoints.Last());
	}
}

const float FUnistrokePoint::PathLength(const TArray<FUnistrokePoint> &Points)
{
	float TotalDistance = 0.0f;

	for (int i = 1; i < Points.Num(); ++i)
	{
		TotalDistance += Distance(Points[i - 1], Points[i]);
	}

	return TotalDistance;
}

const float FUnistrokePoint::Distance(const FUnistrokePoint &PointA, const FUnistrokePoint &PointB)
{
	const float dx = PointB.X - PointA.X;
	const float dy = PointB.Y - PointA.Y;

	return FMath::Sqrt(FMath::Square(dx) + FMath::Square(dy));
}

const float FUnistrokePoint::IndicativeAngle(const TArray<FUnistrokePoint>& Points)
{
	const FUnistrokePoint CentroidPoint = Centroid(Points);
	return FMath::Atan2(CentroidPoint.Y - Points[0].Y, CentroidPoint.X - Points[0].X);
}

const FUnistrokePoint FUnistrokePoint::Centroid(const TArray<FUnistrokePoint> &Points)
{
	float qx = 0.0f;
	float qy = 0.0f;

	for (const FUnistrokePoint Point : Points)
	{
		qx += Point.X;
		qy += Point.Y;
	}

	qx /= Points.Num();
	qy /= Points.Num();

	return FUnistrokePoint(qx, qy);
}

void FUnistrokePoint::RotateBy(TArray<FUnistrokePoint> &Points, const float &Radians)
{
	const FUnistrokePoint CentroidPoint = Centroid(Points);
	const float Cos = FMath::Cos(Radians);
	const float Sin = FMath::Sin(Radians);
	TArray<FUnistrokePoint> OldPoints = Points;

	Points.Empty();

	for (const FUnistrokePoint &Point : OldPoints)
	{
		const float qx = (Point.X - CentroidPoint.X) * Cos - (Point.Y - CentroidPoint.Y) * Sin + CentroidPoint.X;
		const float qy = (Point.X - CentroidPoint.X) * Sin + (Point.Y - CentroidPoint.Y) * Cos + CentroidPoint.Y;

		Points.Add(FUnistrokePoint(qx, qy));
	}
}

void FUnistrokePoint::ScaleTo(TArray<FUnistrokePoint> &Points, const float &Size)
{
	const FUnistrokeRectangle B = BoundingRect(Points);
	TArray<FUnistrokePoint> OldPoints = Points;

	Points.Empty();

	for (const FUnistrokePoint &Point : OldPoints)
	{
		const float qx = Point.X * (Size / B.Width);
		const float qy = Point.Y * (Size / B.Height);

		Points.Add(FUnistrokePoint(qx, qy));
	}
}

const FUnistrokeRectangle FUnistrokePoint::BoundingRect(const TArray<FUnistrokePoint> &Points)
{
	float MinX = TNumericLimits<float>::Max();
	float MaxX = -TNumericLimits<float>::Max();
	float MinY = TNumericLimits<float>::Max();
	float MaxY = -TNumericLimits<float>::Max();

	for (const FUnistrokePoint &Point : Points)
	{
		MinX = FMath::Min(MinX, Point.X);
		MinY = FMath::Min(MinY, Point.Y);
		MaxX = FMath::Max(MaxX, Point.X);
		MaxY = FMath::Max(MaxY, Point.Y);
	}

	return FUnistrokeRectangle(MinX, MinY, MaxX - MinX, MaxY - MinY);
}

void FUnistrokePoint::TranslateTo(TArray<FUnistrokePoint> &Points, const FUnistrokePoint &Point)
{
	const FUnistrokePoint CentroidPoint = Centroid(Points);
	TArray<FUnistrokePoint> OldPoints = Points;

	Points.Empty();

	for (const FUnistrokePoint &CurrentPoint : OldPoints)
	{
		const float qx = CurrentPoint.X + Point.X - CentroidPoint.X;
		const float qy = CurrentPoint.Y + Point.Y - CentroidPoint.Y;

		Points.Add(FUnistrokePoint(qx, qy));
	}
}

const TArray<float> FUnistrokePoint::Vectorize(const TArray<FUnistrokePoint> &Points)
{
	float Sum = 0.0f;
	TArray<float> Vector;

	for (const FUnistrokePoint &Point : Points)
	{
		Vector.Add(Point.X);
		Vector.Add(Point.Y);
		Sum += FMath::Square(Point.X) + FMath::Square(Point.Y);
	}

	const float Magnitude = FMath::Sqrt(Sum);

	for (float &V : Vector)
	{
		V /= Magnitude;
	}

	return Vector;
}

const float FUnistrokePoint::OptimalCosineDistance(const TArray<float> &VectorA, const TArray<float> &VectorB)
{
	float A = 0.0f;
	float B = 0.0f;

	for (int i = 0; i < VectorA.Num(); i += 2)
	{
		A += VectorA[i] * VectorB[i] + VectorA[i + 1] * VectorB[i + 1];
		B += VectorA[i] * VectorB[i + 1] - VectorA[i + 1] * VectorB[i];
	}

	const float Angle = FMath::Atan(B / A);

	return FMath::Acos(A * FMath::Cos(Angle) + B * FMath::Sin(Angle));
}

const float FUnistrokePoint::DistanceAtBestAngle(const TArray<FUnistrokePoint> &Points, const TArray<FUnistrokePoint> &TemplatePoints, const float &FromAngle, const float &ToAngle, const float &Threshold)
{
	float fromAngle = FromAngle;
	float toAngle = ToAngle;
	float x1, x2, f1, f2;
	
	GSS(fromAngle, toAngle, Points, TemplatePoints, x1, f1);
	GSS(toAngle, fromAngle, Points, TemplatePoints, x2, f2);
	
	while (FMath::Abs(toAngle - fromAngle) > Threshold)
	{
		if (f1 < f2)
		{
			toAngle = x2;
			x2 = x1;
			f2 = f1;
			GSS(fromAngle, toAngle, Points, TemplatePoints, x1, f1);
		} else {
			fromAngle = x1;
			x1 = x2;
			f1 = f2;
			GSS(toAngle, fromAngle, Points, TemplatePoints, x2, f2);
		}
	}

	return FMath::Min(f1, f2);
}

void FUnistrokePoint::GSS(const float &a, const float &b, const TArray<FUnistrokePoint>& Points, const TArray<FUnistrokePoint>& TemplatePoints, float &x, float &f)
{
	x = Phi * a + (1.0 - Phi) * b;
	f = DistanceAtAngle(Points, TemplatePoints, x);
}

const float FUnistrokePoint::DistanceAtAngle(const TArray<FUnistrokePoint> &Points, const TArray<FUnistrokePoint> &TemplatePoints, const float &Radians)
{
	TArray<FUnistrokePoint> NewPoints = Points;
	RotateBy(NewPoints, Radians);
	return PathDistance(NewPoints, TemplatePoints);
}

const float FUnistrokePoint::PathDistance(const TArray<FUnistrokePoint> &PathA, const TArray<FUnistrokePoint> &PathB)
{
	if (PathA.Num() != PathB.Num()) return TNumericLimits<float>::Max();

	float D = 0.0f;

	for (int i = 0; i < PathA.Num(); ++i)
	{
		D += Distance(PathA[i], PathB[i]);
	}

	return (D / PathA.Num());
}

FUnistrokePoint::~FUnistrokePoint()
{
}
