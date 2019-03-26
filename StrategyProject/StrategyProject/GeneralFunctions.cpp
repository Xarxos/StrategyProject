#include "stdafx.h"
#include <cstdlib>

int numDigits(int number)
{
	int digits = 1;

	while (number >= 10)
	{
		number /= 10;
		digits++;
	}

	return digits;
}

int getRandomInt(const int min, const int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);

	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

double getRandomDouble(const double min, const double max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);

	return (rand() * fraction * (max - min + 1) + min);
}