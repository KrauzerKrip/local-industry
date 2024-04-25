#pragma once


class PointerOverGui {
public:
	virtual ~PointerOverGui() = default;

	virtual bool isPointerOverGui() = 0;
};