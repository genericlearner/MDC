#include "ASTFactory.h"

std::vector<AST*>treesProduced;

AST* ASTFactory::makeNode(Token token) {
	switch (token.getType()) {
	case TokenType::INTEGER_VAL:
		treesProduced.push_back(new )
	}
}