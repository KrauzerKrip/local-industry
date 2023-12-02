#include "gl_widget_zoffset_calculator.h"

float WidgetZOffsetCalculatorGl::calculateZOffset(unsigned int layerNumber) {
	return ((float)layerNumber) / 100; // should not be bigger than 2
}
