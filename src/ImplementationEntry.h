#pragma once
#include "SymbolTableEntry.h"
#include <vector>

class ImplementationEntry : public SymbolTableEntry {
public:
	ImplementationEntry();
	SymbolTable* contClass;

	std::string classImplement;

	virtual int compSize() override;
	virtual std::string toStr() override;
	virtual std::string toDot() override;
};