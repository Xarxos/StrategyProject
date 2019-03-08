#pragma once

template <typename T>
struct Property
{
	T actualValue;
	bool exactValueIsKnown;
	T lowestValueKnown;
	T highestValueKnown;
};