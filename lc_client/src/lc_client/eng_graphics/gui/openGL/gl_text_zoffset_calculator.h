#pragma once

#include "lc_client/eng_graphics/gui/zoffset_calculator.h"


class TextZOffsetCalculatorGl : public ZOffsetCalculator {
public:
	float calculateZOffset(unsigned int layerNumber) const override;
};
