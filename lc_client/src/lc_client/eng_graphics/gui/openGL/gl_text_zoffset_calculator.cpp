#include "gl_text_zoffset_calculator.h"

float TextZOffsetCalculatorGl::calculateZOffset(unsigned int layerNumber) { 
	return ((float)layerNumber + 0.5f) / 100; // should not be bigger than 2
}
