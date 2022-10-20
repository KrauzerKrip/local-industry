#pragma once

#include <cmrc/cmrc.hpp>

CMRC_DECLARE(eng_resources);


class ShaderManager {
public:
	ShaderManager();
	~ShaderManager();
	void loadShaders();
};
