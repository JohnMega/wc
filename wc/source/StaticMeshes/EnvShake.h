#pragma once

#include "Circle.h"

class EnvShake : public Circle
{
private:
	float shakePower;

public:
	EnvShake(COORDS centreCoord, COORDS normVec, const std::string& bmpName, float rad, int color, float shakePower)
		: Circle(centreCoord, normVec, bmpName, rad, color)
	{
		this->shakePower = shakePower;
	}

	float GetShakePower() const noexcept
	{
		return shakePower;
	}
};