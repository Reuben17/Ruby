#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

namespace Ruby { namespace Maths {

	inline float toRadians(float degrees)
	{
		return degrees * (float)(M_PI / 180.0f);
	}

}}