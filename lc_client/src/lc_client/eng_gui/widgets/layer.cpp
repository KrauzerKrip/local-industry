#include "layer.h"

Layer::Layer(ZOffsetCalculator* pZOffsetCalculator) { m_pZOffsetCalculator = pZOffsetCalculator; }

void Layer::setLayerNumber(unsigned int number) { m_layerNumber = number; }

float Layer::getOffsetZ() { return m_pZOffsetCalculator->calculateZOffset(m_layerNumber); }