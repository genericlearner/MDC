#pragma once
#include "tokenAST.h"

class ID : public TokenAST {
public:
	ID(Token t);
	virtual std::string toString() override;
};