#pragma once
#include <string>
#include "parserUtility.h"
#include "SymbolTable.h"

class SymbolTableEntry {
protected:
	SymbolTableEntry();
public:
	std::string name="";
	std::string vis= "";
	SymbolTable* link;
	int offset = 0;

	virtual std::string toStr() = 0;
	virtual std::string toDot() = 0;

	virtual int compSize() = 0;
	virtual int getOffset();
};