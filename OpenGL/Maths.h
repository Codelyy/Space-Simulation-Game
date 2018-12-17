#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

namespace Maths
{
	float DegreesToRadians(float value)
	{
		return value * (M_PI / 180);
	}
};