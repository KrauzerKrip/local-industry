#pragma once

#include <vector>
#include <utility>
#include "layout.h"

class Grid : public Layout {
public:
	Grid(unsigned int columnNumber, float padding, float rowHeight);

	void updateChildWidgets();

private:
	unsigned int m_columnNumber;
	float m_padding; 
	float m_rowHeight; 
};