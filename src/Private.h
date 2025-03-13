#pragma once
#include "tokenAST.h"

class Private : public TokenAST {
public:
	Private(Token t);
	virtual std::string toString() override;
};