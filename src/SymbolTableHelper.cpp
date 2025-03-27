#include "SymbolTableHelper.h"

std::vector<SymbolTableEntry*>SymbolTableHelper::recRef;
std::vector<SymbolTable*>SymbolTableHelper::tableRef;
SymbolTable* SymbolTableHelper::createSymbolTable() {
	SymbolTable* table = new SymbolTable();
	tableRef.push_back(table);
	return table;
}

VariableEntry* SymbolTableHelper::createSymbolVariableRec() {
	VariableEntry* rec = new VariableEntry();
	recRef.push_back(rec);
	return rec;
}

ClassEntry* SymbolTableHelper::createSymbolClassRec() {
	ClassEntry* rec = new ClassEntry();
	recRef.push_back(rec);
	return rec;
}

FunctionEntry* SymbolTableHelper::createSymbolFunctionRec() {
	FunctionEntry* rec = new FunctionEntry();
	recRef.push_back(rec);
	return rec;
}

TempEntry* SymbolTableHelper::createSymbolTempRec() {
	TempEntry* rec = new TempEntry();
	recRef.push_back(rec);
	return rec;
}

ParamEntry* SymbolTableHelper::createSymbolParamRec() {
	ParamEntry* rec = new ParamEntry();
	recRef.push_back(rec);
	return rec;
}

ImplementationEntry* SymbolTableHelper::createSymbolImplementationRec() {
	ImplementationEntry* rec = new ImplementationEntry();
	recRef.push_back(rec);
	return rec;
}