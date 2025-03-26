#pragma once
#include "VisibilityEntry.h"
#include <vector>
#include <tuple>

class FunctionEntry : public VisibilityEntry {
	std::string signString();

public:
	FunctionEntry();
	SymbolTable* contClass;
	std::string classMethod;

	std::string returnType;
	std::vector<std::tuple<std::string, std::string, std::vector<int>>>paramList;
	virtual std::string toStr() override;
	virtual std::string toDot() override;
	virtual int compSize() override;
	virtual bool compare(FunctionEntry* fEntry);
	

};