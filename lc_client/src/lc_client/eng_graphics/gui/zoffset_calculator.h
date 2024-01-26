#pragma once


class ZOffsetCalculator {
public:
	virtual float calculateZOffset(unsigned int layerNumber) const = 0;
};
