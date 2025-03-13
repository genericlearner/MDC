#pragma once
#include "tokenAST.h"
#include "Lexer/Token.h"
#include <string>

class IntLit : public TokenAST {
public:
	IntLit(Token t);
	virtual std::string toString() override;
};