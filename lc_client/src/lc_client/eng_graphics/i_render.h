#pragma once

class IRender {
public:
	virtual ~IRender() {};

	virtual void init() = 0;
	virtual void render() = 0;
	virtual void clear() = 0;
	virtual void cleanUp() = 0;
};