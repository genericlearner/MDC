#pragma once
#include "tokenAST.h"

class Void : public TokenAST {
public:
	Void(Token t);
	virtual std::string toString() override;
};