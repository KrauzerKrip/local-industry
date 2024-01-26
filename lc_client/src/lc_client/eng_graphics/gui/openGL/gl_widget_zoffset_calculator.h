#pragma once

#include "lc_client/eng_graphics/gui/zoffset_calculator.h"


class WidgetZOffsetCalculatorGl : public ZOffsetCalculator {
public:
	float calculateZOffset(unsigned int layerNumber) const override;
};
