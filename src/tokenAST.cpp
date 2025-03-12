#include "tokenAST.h"

TokenAST::TokenAST(Token t):t(t){}

Token TokenAST::getToken() {
	return t;
}

std::string TokenAST::getLexeme() {
	return t.getLexeme();
}

