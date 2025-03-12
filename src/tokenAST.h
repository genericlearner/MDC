#pragma once
#include "AST.h"
#include <string>
#include "Lexer/Token.h"

class TokenAST : public AST {
private:
	Token t;
public:
	TokenAST(Token t);
	Token getToken();
	std::string getLexeme();
	virtual std::string toString() = 0;
	//virtual std::string getData() override;
};