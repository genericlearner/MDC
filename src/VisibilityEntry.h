#pragma once
#include "SymbolTableEntry.h"

class VisibilityEntry : public SymbolTableEntry {
public:
	std::string visibility;
	VisibilityEntry();

	virtual std::string toStr() = 0;
	virtual std::string toDot() = 0;
};