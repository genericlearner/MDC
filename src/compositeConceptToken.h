#pragma once
#include "tokenAST.h"
#include <sstream>


class CompositeConceptTokenAST :public TokenAST {
public:
	CompositeConceptTokenAST(Token t);

	virtual std::string toString() override;
};