#include "AST.h"
#include "ASTFactory.h"
#include "Lexer/Token.h"
#include "SymbolTableEntry.h"
#include "VariableEntry.h"
#include "FunctionEntry.h"
#include "ClassEntry.h"
#include "ParamEntry.h"
#include <iostream>
#include <sstream>


AST::AST():
	rightSibling(nullptr),
	leftMostChild(nullptr),
	leftMostSibling(this),
	parent(nullptr),

	symbolRecord(nullptr),
	symbolTable(nullptr)
{
}

AST::~AST(){
	std::cout << "deleting objects" << std::endl;

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

/*
void AST::accept(Visitor* visitor, bool depthSearch)
{
}*/

void AST::setSymbolTable(SymbolTable* symbolTable) {
	this->symbolTable = symbolTable;
	this->symbolTable->setName(toString());
	this->symbolTable->setNode(this);
}
std::vector<ParamEntry*>AST::searchParam(std::string name) {
	std::vector<ParamEntry*>res;

	if (symbolTable) {
		if (ParamEntry* pr = symbolTable->findParRec(name)) {
			res.emplace_back(pr);
		}
	}
	if (parent) {
		std::vector<ParamEntry*>parRes = parent->searchParam(name);
		res.insert(res.end(), parRes.begin(), parRes.end());
	}
	return res;
}
std::vector<VariableEntry*> AST::searchVariabe(std::string name) {
	std::vector<VariableEntry*>res;

	//if (FunctionEntry* functionRec = dynamic_cast<FunctionEntry*>(symbolRecord)) {
	//	if (functionRec && functionRec->contClass) {
	//		functionRec->contClass->findVariableRec(name);
	//	}
	//}

	if (symbolTable) {
		if (VariableEntry* vr = symbolTable->findVariableRec(name)) {
			res.emplace_back(vr);
		}
	}
	// If not found, check if we are inside a method and search class variables
	if (symbolRecord && dynamic_cast<FunctionEntry*>(symbolRecord)) {
		FunctionEntry* functionEntry = dynamic_cast<FunctionEntry*>(symbolRecord);
		if (functionEntry->contClass) {  // Check if function is inside a class
			VariableEntry* classVar = functionEntry->contClass->findVariableRec(name);
			if (classVar) {
				res.emplace_back(classVar);
			}
		}
	}
	if (parent) {
		std::vector<VariableEntry*> parentRes = parent->searchVariabe(name);
		res.insert(res.end(), parentRes.begin(), parentRes.end());
	}
	return res;
}

std::vector<FunctionEntry*>AST::searchFunction(std::string name) {
	std::vector<FunctionEntry*>res;

	if (symbolTable) {
		std::vector<FunctionEntry*>functionEntryInTable = symbolTable->findFunctionRec(name);
		if (functionEntryInTable.size() > 0) {
			res.insert(res.end(), functionEntryInTable.begin(), functionEntryInTable.end());
		}
	}

	if (parent) {
		std::vector<FunctionEntry*>parentRes = parent->searchFunction(name);
		res.insert(res.end(), parentRes.begin(), parentRes.end());

	}
	return res;
}

ClassEntry* AST::searchClass(std::string name) {
	if (symbolTable) {
		ClassEntry* res = symbolTable->findClassRec(name);
		if (res) {
			return res;
		}
	}

	if (parent) {
		return parent->searchClass(name);
	}

	return nullptr;
}

void AST::insertIntoTable(SymbolTableEntry* data) {
	SymbolTable* table = getClosestTable();
	table->insertRec(data);
}

SymbolTable* AST::getClosestTable() {
	if (symbolTable) {
		return symbolTable;
	}
	else if (parent) {
		return parent->getClosestTable();
	}
	else return nullptr;
}

AST* AST::makeSiblings(AST* y) {
	if (!y) {
		return nullptr;
	} 

	// find the rightmode node in this sibling list
	AST* xsibs = this;
	while (xsibs->rightSibling != nullptr) {
		xsibs = xsibs->rightSibling;
	}

	// join the lists
	AST* ysibs = y->leftMostSibling;
	xsibs->rightSibling = ysibs;

	// set points for the new siblings
	ysibs->leftMostSibling = xsibs->leftMostSibling;
	ysibs->parent = xsibs->parent;

	while (ysibs->rightSibling != nullptr) {
		ysibs = ysibs->rightSibling;
		ysibs->leftMostSibling = xsibs->leftMostSibling;
		ysibs->parent = xsibs->parent;
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
