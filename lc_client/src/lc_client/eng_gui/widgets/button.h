#pragma once

#include <functional>

#include "text_widget.h"
#include "lc_client/eng_gui/input/input_receiver.h"


class Button : public TextWidget, public InputReceiver {
public:
	Button(GuiDependencies dependencies);

	void mouseClick(MouseClickEvent event);
	void keyPressed(KeyEvent event);
	void characterInput(std::string character);
	void scroll(ScrollEvent event) override;
	void setCallback(std::function<void()> callback);
	void setBackground(Background* pBackground) override;
	void setHoverBackground(Background* pBackground);
	void setClickBackground(Background* pBackground);
	virtual void click();
	void render() override;

private:
	std::function<void()> m_callback;
	Background* m_pDefaultBackground = nullptr;
	Background* m_pHoverBackground = nullptr;
	Background* m_pClickBackground = nullptr;

	InputController* m_pInputController = nullptr;
};
