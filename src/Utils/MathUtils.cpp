#include "MathUtils.h"
#include <cmath>

int MathUtils::getSign(const double & value)
{
	if (value == 0)
		return 1;
	return (int)(abs(value) / value);
}
