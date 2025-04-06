#pragma once
#include <string>
#include <vector>
#include "SymbolTable.h"
#include "SymbolTableEntry.h"
#include <iostream>
class Visitor;

class AST {
private:
	std::string data;
	std::string type;

	std::string assemblyData;

	SymbolTable* symbolTable;
	SymbolTableEntry* symbolRecord;

public:
	AST* leftMostSibling;
	AST* leftMostChild;
	AST* rightSibling;
	AST* parent;

	AST();
	~AST();

	std::vector<AST*> getChildren();

	AST* getChild(int c);

	AST* makeSiblings(AST* y);
	void adoptChild(AST* y);

	virtual std::string toString() = 0;
	std::string dotConvert();
	virtual void accept(Visitor* visitor, bool depthSearch = true) = 0;

	virtual std::string getData() { return data; }
	virtual void setData(std::string data) { this->data = data; }

	virtual std::string getAssemblyData() { return assemblyData; }
	virtual void setAssemblyData(std::string data) { this->data = data; }


	SymbolTableEntry* getSymbolRec() { return symbolRecord; }
	void setSymbolRec(SymbolTableEntry* data) { this->symbolRecord = data; }

	SymbolTable* getSymbolTable() { 
		if (symbolTable == nullptr) {
			std::cout << "Table is null" << std::endl;
			return nullptr;
		}
		return symbolTable; }
	void setSymbolTable(SymbolTable* symbolTable);

	std::string getType() { return type; }
	void setType(std::string type) { this->type = type; }

	std::vector<VariableEntry*>searchVariabe(std::string name);
	std::vector<FunctionEntry*>searchFunction(std::string name);
	std::vector<ParamEntry*>searchParam(std::string name);
	ClassEntry* searchClass(std::string name);

	void insertIntoTable(SymbolTableEntry* data);
	SymbolTable* getClosestTable();


};