#pragma once

class IGameLogic {
public:
	virtual ~IGameLogic() {};

	virtual void init() = 0;
	virtual void input(double deltaTime) = 0;
	virtual void update(double updateInterval) = 0;
	virtual void render() = 0;
	virtual void cleanUp() = 0;
};