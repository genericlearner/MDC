#include "tokenAST.h"

TokenAST::TokenAST(Token token):token(token){}

Token TokenAST::getToken() {
	return token;
}

std::string TokenAST::getLexeme() {
	return token.getLexeme();
}

