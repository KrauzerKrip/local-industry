#include "../../eng_graphics/i_window.h"

#include <GLFW/glfw3.h>

class WindowGL : public IWindow {
public:

	WindowGL();
	~WindowGL();

	void init();
	void update();

private:
	GLFWwindow
};