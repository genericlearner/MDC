#pragma once
#include "SymbolTableEntry.h"
#include <vector>

class ClassEntry : public SymbolTableEntry {
public:
	ClassEntry();
	virtual int compSize() override;
	virtual std::string toStr() override;
	virtual std::string toDot() override;
};