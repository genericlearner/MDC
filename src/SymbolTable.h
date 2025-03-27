#pragma once
#include <vector>
#include <string>


class AST;
class SymbolTableEntry;
class ClassEntry;
class FunctionEntry;
class ParamEntry;
class VariableEntry;
class TempEntry;
class ImplementationEntry;

class SymbolTable {

private:
	AST* ast_node;
	std::vector<SymbolTableEntry* > table;
	std::string name;
public:
	SymbolTable();

	void insertRec(SymbolTableEntry* e);

	std::vector<ClassEntry*> getClassRec();
	std::vector<FunctionEntry*> getFuncRec();
	std::vector<ParamEntry*> getParRec();
	std::vector<VariableEntry*> getVarRec();
	std::vector<TempEntry*> getTempRec();
	std::vector<ImplementationEntry*>getImplementationRec();
	
	ClassEntry* findClassRec(std::string name);
	std::vector<FunctionEntry*>findFunctionRec(std::string name);
	ParamEntry* findParRec(std::string name);
	TempEntry* findTempRec(std::string nam);
	VariableEntry* findVariableRec(std::string name);
	SymbolTableEntry* findVarOrParRec(std::string name);
	ImplementationEntry* findImplementationRec(std::string name);

	std::string getName() { return name; };
	void setName(std::string name) { this->name = name; }
	void setNode(AST* node) { this->ast_node = node; }
	AST* getNode() { return ast_node; };
	
	int compOffset();
	int compSize();

	std::string toDot();


};