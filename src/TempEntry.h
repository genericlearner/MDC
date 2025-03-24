#pragma once
#include "SymbolTableEntry.h"
#include <string>
#include <vector>
class TempEntry : public SymbolTableEntry {
public:
	TempEntry();

	std::string data;
	std::string type;

	virtual std::string toStr() override;
	virtual std::string toDot() override;

	virtual int compSize() override;
}