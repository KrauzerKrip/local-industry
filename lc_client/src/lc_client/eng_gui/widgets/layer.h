#pragma once

#include "lc_client/eng_graphics/gui/zoffset_calculator.h"


class Layer {
public:
	Layer(ZOffsetCalculator* pZOffsetCalculator);

	void setLayerNumber(unsigned int number);
	float getOffsetZ();
	unsigned int getLayerNumber();

private:
	ZOffsetCalculator* m_pZOffsetCalculator;
	unsigned int m_layerNumber;
};
