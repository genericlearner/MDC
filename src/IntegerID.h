#pragma once
#include "tokenAST.h"

class IntegerID : public TokenAST {
public:
	IntegerID(Token c);

	virtual std::string toString() override;
};