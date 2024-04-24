#pragma once

#include "layout.h"


class VerticalScrollArea : public Layout {
public:
	VerticalScrollArea();

	void updateChildWidgets() override;

	float getScroll();
	/**
	 * @brief
	 * @param scroll: percentage of scroll. D = [0, 1].
	 */
	void setScroll(float scroll);
	void setSpacing(unsigned int spacing);
	/**
	 * @brief scrolls the area by given value, regardless of the size of the area and content.
	 * @param offset. D = R;
	 */
	void scroll(float offset);

	int getContentSize();
	int getNotFittingSize();
	void clearWidgets();

private:
	float m_scroll;
	unsigned int m_spacing;

	int m_contentSize; 
	int m_notFittingSize; 
};
