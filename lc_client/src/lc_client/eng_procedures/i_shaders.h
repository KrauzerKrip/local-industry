#pragma once

class IShaderManager {
public:
	virtual ~IShaderManager() {};

	virtual void loadShaders() = 0;
};