#pragma once
#include "visibility.h"
#include "Lexer/Token.h"
#include "VisibilityEntry.h"
#include <vector>
#include "AST.h"

using std::vector;

class VariableEntry : public VisibilityEntry {
	std::string generateSign();
public:
	std::string visbility;
	std::string type;
	std::vector<int> arrayDimension;

	VariableEntry();
	virtual std::string toStr() override;
	virtual std::string toDot() override;
	virtual int compSize() override;
};