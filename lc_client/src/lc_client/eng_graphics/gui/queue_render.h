#pragma once


class QueueRender {
public:
	virtual ~QueueRender() {};

	virtual void renderQueue() = 0;
};
