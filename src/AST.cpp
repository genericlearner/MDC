#include "AST.h"
#include "ASTFactory.h"
#include "Lexer/Token.h"
#include <iostream>
#include <sstream>


AST::AST() {
	rightSibling = nullptr;
	leftMostChild = nullptr;
	leftMostSibling = this;
	parent = nullptr;
}

AST::~AST(){}
std::string AST::dotConvert() {
	std::stringstream ss;
	AST* child = leftMostChild;

	std::string curr = this->toString();

	while (child != nullptr) {
		ss << "\"" + curr + "\"->\"" + child->toString() + "\"\n";
		ss << child->dotConvert();
		child = child->rightSibling;
	}

	return ss.str();
}
std::vector<AST*> AST::getChildren() {
	std::vector<AST*> children;
	AST* child = leftMostChild;

	while (child != nullptr) {
		children.push_back(child);
		child = child->rightSibling;
	}
	return children;

}

AST* AST::getChild(int c) {
	AST* child = leftMostChild;
	int count = 0;
	while (child != nullptr && count != c) {
		child = child->rightSibling;
		count++;
	}

	return child;
}

AST* AST::makeSiblings(AST* y) {
	if (!y) {
		return nullptr;
	}

	AST* sibs = this;
	while (sibs->rightSibling != nullptr) {
		sibs = sibs->rightSibling;
	}

	AST* ysibs = y->leftMostSibling;
	sibs->rightSibling = ysibs;

	ysibs->leftMostSibling = sibs->leftMostSibling;
	ysibs->parent = sibs->parent;

	while (ysibs->rightSibling != nullptr) {
		ysibs = ysibs->rightSibling;
		ysibs->leftMostSibling = sibs->leftMostSibling;
		ysibs->parent = sibs->parent;
	}

	return ysibs;

}

void AST::adoptChild(AST* y) {
	if (this->leftMostChild != nullptr) {
		this->leftMostChild->makeSiblings(y);
	}
	else {
		AST* ysibs = y->leftMostSibling;
		this->leftMostChild = ysibs;

		while (ysibs != nullptr) {
			ysibs->parent = this;
			ysibs = ysibs->rightSibling;
		}

	}
}
