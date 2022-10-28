#pragma once 

#include <string>

struct Properties {
	std::string uuid;
	std::string id;

	Properties() = default;
	Properties(std::string uuid, std::string id) : uuid(uuid), id(id) {};
	Properties(const Properties&) = default;
};
