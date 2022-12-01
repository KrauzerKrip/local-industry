#pragma once

class IGameLogic {
public:
	virtual ~IGameLogic() {};

	virtual void init() = 0;
	virtual void input() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void cleanUp() = 0;
};