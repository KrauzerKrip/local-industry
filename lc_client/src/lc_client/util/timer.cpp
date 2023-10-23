#include "timer.h"

#include <windows.h>

void Timer::showWindow() {
	stop();
	//MessageBox(NULL, std::to_string(elapsedMilliseconds()).c_str(), "Time elapsed:", MB_OK); 
}
