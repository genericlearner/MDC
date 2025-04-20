#pragma once
#include "AST.h"
#include <string>
#include "Lexer/Token.h"

class TokenAST : public AST {
private:
	Token token;
public:
	TokenAST(Token token);
	Token getToken();
	std::string getLexeme();
	virtual std::string toString() = 0;
	virtual std::string getData() override;
	virtual std::string getAssemblyData() override;
};