#pragma once
#include "Lexer/Token.h"
#include "AST.h"
#include "Lexer/lexer.h"
#include "parserUtility.h"
#include <vector>


class ASTFactory {
private: 
	static std::vector<AST*> trees;

public:
	static AST* makeNode(Token token);
	static AST* makeNode(compositeConcept cc);

	static AST* makeFamily(compositeConcept cc, std::vector<AST*>children);
	static void makeFamily(AST* parent, std::vector<AST*>children);

};