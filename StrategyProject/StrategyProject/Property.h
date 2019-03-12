#pragma once

template <typename T>
struct Property
{
	T actualValue;
	bool exactValueIsKnown = false;
	T lowestValueKnown;
	T highestValueKnown;
};