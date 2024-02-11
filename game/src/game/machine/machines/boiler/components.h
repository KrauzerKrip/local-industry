#pragma once


struct Boiler {
	float waterVolume;

	Boiler() : waterVolume(0) {}
	Boiler(float waterVolume) : waterVolume(waterVolume) {}
};