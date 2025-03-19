#pragma once
#include "tokenAST.h"

class IntegerID : public TokenAST {
public:
	IntegerID(Token t);

	virtual std::string toString() override;
};