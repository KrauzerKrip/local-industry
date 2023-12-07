#include "gl_widget_zoffset_calculator.h"

float WidgetZOffsetCalculatorGl::calculateZOffset(unsigned int layerNumber) {
	return ((float)layerNumber) / 100.0f; // should not be bigger than 2
}
