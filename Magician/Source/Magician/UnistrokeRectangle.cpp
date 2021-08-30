#include "UnistrokeRectangle.h"

FUnistrokeRectangle::FUnistrokeRectangle()
{
	X = 0.0f;
	Y = 0.0f;
	Width = 0.0f;
	Height = 0.0f;
}

FUnistrokeRectangle::FUnistrokeRectangle(const float &X, const float &Y, const float &Width, const float &Height)
{
	this->X = X;
	this->Y = Y;
	this->Width = Width;
	this->Height = Height;
}

FUnistrokeRectangle::~FUnistrokeRectangle()
{
}
