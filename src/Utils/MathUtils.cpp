#include "MathUtils.h"
#include <cmath>

double MathUtils::getSign(const double & value)
{
	return abs(value) / value;
}
