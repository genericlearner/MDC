#pragma once
#include "tokenAST.h"

class FloatLit : public TokenAST {
public:
	FloatLit(Token t);
	virtual std::string toString() override;
};
