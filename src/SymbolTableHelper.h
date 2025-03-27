#pragma once
#include "SymbolTable.h"
#include "SymbolTableEntry.h"
#include "ClassEntry.h"
#include "FunctionEntry.h"
#include "TempEntry.h"
#include "VariableEntry.h"
#include "ParamEntry.h"
#include "ImplementationEntry.h"
#include <vector>


class SymbolTableHelper {
	static std::vector<SymbolTableEntry*>recRef;
	static std::vector<SymbolTable*>tableRef;

public:
	static SymbolTable* createSymbolTable();

	static VariableEntry* createSymbolVariableRec();
	static ClassEntry* createSymbolClassRec();
	static FunctionEntry* createSymbolFunctionRec();
	static TempEntry* createSymbolTempRec();
	static ParamEntry* createSymbolParamRec();
	static ImplementationEntry* createSymbolImplementationRec();

};