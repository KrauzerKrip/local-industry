#pragma once

#include <vector>

#include "lc_client/eng_gui/widgets/widget.h"


enum class WidgetSides : uint32_t {NONE = 0, TOP = (1 << 0), BOTTOM = (1 << 1), LEFT = (1 << 2), RIGHT = (1 << 3) };

constexpr enum WidgetSides operator|(const enum WidgetSides selfValue, const enum WidgetSides inValue) {
	return (enum WidgetSides)(uint32_t(selfValue) | uint32_t(inValue));
}

constexpr enum WidgetSides operator&(const enum WidgetSides selfValue, const enum WidgetSides inValue) {
	return (enum WidgetSides)(uint32_t(selfValue) & uint32_t(inValue));
}


struct AnchoredWidget {
	Widget* pWidget = nullptr;
	WidgetSides widgetSides;;
};


/**
 * \brief Isn`t ready yet.
 */
class Anchor {
public:
	void addWidget(Widget* pWidget);
	void addWidget(Widget* pWidget, const WidgetSides sides);
	void updateChildWidgets(glm::vec2 paneSize);

    /**
     * \brief percentage position should have values = [0.0, 1.0]. 
     */
    glm::vec2 m_percentagePosition;
	Widget* m_pGizmoWidget = nullptr;
    std::vector<AnchoredWidget> m_widgets;

private:
	bool checkSide(WidgetSides sides, WidgetSides side);
};


class AnchorPane : public Layout {
public:
	void addAnchor(Anchor* pAnchor);
	void updateChildWidgets() override;

private:
	std::vector<Anchor*> m_anchors; 
};