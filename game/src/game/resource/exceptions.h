#pragma once

#include <stdexcept>


class InvalidExtractionInProgressException : public std::runtime_error {
public:
	InvalidExtractionInProgressException() : std::runtime_error("DepositTaskSystem: deposit.resource != inventoryLoaded.item") {}
};