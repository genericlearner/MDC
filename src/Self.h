#pragma once
#include "tokenAST.h"

class Self : public TokenAST {
public:
	Self(Token t);
	virtual std::string toString() override;
};