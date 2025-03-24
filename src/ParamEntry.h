#pragma once
#include "SymbolTableEntry.h"
#include <vector>
#include <string>

class ParamEntry : public SymbolTableEntry {
	std::string generateSign();

public:
	std::string type;
	std::vector<int>arrInd;

	ParamEntry();

	virtual std::string toStr() override;
	virtual std::string toDot() override;
	virtual int compSize() override;
};