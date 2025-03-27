#include "SymbolTable.h"
#include "SymbolTableEntry.h"
#include "ClassEntry.h"
#include "FunctionEntry.h"
#include "ParamEntry.h"
#include "VariableEntry.h"
#include "ImplementationEntry.h"
#include "TempEntry.h"
#include <sstream>

SymbolTable::SymbolTable() {
	ast_node = nullptr;
}
void SymbolTable::insertRec(SymbolTableEntry* se) {
	this->table.push_back(se);

	compOffset();
}

std::vector<ClassEntry*> SymbolTable::getClassRec() {
	std::vector<ClassEntry*> symbolEntries;

	for (SymbolTableEntry* entry : table) {
		ClassEntry* cast = dynamic_cast<ClassEntry*>(entry);
		if (cast != nullptr) {
			symbolEntries.push_back(cast);
		}
		
	}

	return symbolEntries;
}

std::vector<VariableEntry*> SymbolTable::getVarRec() {
	std::vector<VariableEntry*> symbolEntries;

	for (SymbolTableEntry* entry : table) {
		VariableEntry* cast = dynamic_cast<VariableEntry*>(entry);
		if (cast != nullptr) {
			symbolEntries.push_back(cast);
		}

	}

	return symbolEntries;
}

std::vector<FunctionEntry*>SymbolTable::getFuncRec() {
	std::vector<FunctionEntry*>symbolEntries;

	for (SymbolTableEntry* entry : table) {
		FunctionEntry* cast = dynamic_cast<FunctionEntry*>(entry);
		if (cast != nullptr) {
			symbolEntries.push_back(cast);
		}
	}
	return symbolEntries;
}
std::vector<ParamEntry*>SymbolTable::getParRec() {
	std::vector<ParamEntry*>symbolEntries;

	for (SymbolTableEntry* entry : table) {
		ParamEntry* cast = dynamic_cast<ParamEntry*>(entry);
		if (cast != nullptr) {
			symbolEntries.push_back(cast);
		}
	}
	return symbolEntries;
}

std::vector<TempEntry*>SymbolTable::getTempRec() {
	std::vector<TempEntry*>symbolEntries;

	for (SymbolTableEntry* entry : table) {
		TempEntry* cast = dynamic_cast<TempEntry*>(entry);
		
		if (cast != nullptr) {
			symbolEntries.push_back(cast);
		}
	}
	return symbolEntries;

}

std::vector<ImplementationEntry*>SymbolTable::getImplementationRec() {
	std::vector<ImplementationEntry*>symbolEntries;

	for (SymbolTableEntry* entry : table) {
		ImplementationEntry* cast = dynamic_cast<ImplementationEntry*>(entry);
		
		if (cast != nullptr) {
			symbolEntries.push_back(cast);
		}
	}
	return symbolEntries;
}

ClassEntry* SymbolTable::findClassRec(std::string name) {
	std::vector<ClassEntry*>symbolEntries = getClassRec();

	ClassEntry* foundClass = nullptr;

	for (ClassEntry* entry : symbolEntries) {
		if (entry->name == name) {
			foundClass = entry;
			break;
		}
	}
	return foundClass;
}

std::vector<FunctionEntry*>SymbolTable::findFunctionRec(std::string name) {
	std::vector<FunctionEntry*>symbolEntries = getFuncRec();
	std::vector<FunctionEntry*>foundFunction;

	for (FunctionEntry* entry : symbolEntries) {
		if (entry->name == name) {
			foundFunction.push_back(entry);
		}
	}

	return foundFunction;
}

ParamEntry* SymbolTable::findParRec(std::string name) {
	std::vector<ParamEntry*>symbolEntries = getParRec();
	ParamEntry* foundParam = nullptr;
	for (ParamEntry* entry : symbolEntries) {
		if (entry->name == name) {
			foundParam = entry;
			break;
		}
	}
	return foundParam;
}

VariableEntry* SymbolTable::findVariableRec(std::string name) {
	std::vector<VariableEntry*>symbolEntries = getVarRec();
	VariableEntry* foundVariable = nullptr;

	for (VariableEntry* entry : symbolEntries) {
		if (entry->name ==  name) {
			foundVariable = entry;
			break;
		}
	}
	return foundVariable;
}

TempEntry* SymbolTable::findTempRec(std::string name) {
	std::vector<TempEntry*>symbolEntries = getTempRec();
	TempEntry* foundTemp = nullptr;

	for (TempEntry* entry : symbolEntries) {
		if (entry->name == name) {
			foundTemp = entry;
			break;
		}
	}
	return foundTemp;
}
ImplementationEntry* SymbolTable::findImplementationRec(std::string name) {
	std::vector<ImplementationEntry*>symbolEntries = getImplementationRec();

	ImplementationEntry* foundImpl = nullptr;

	for (ImplementationEntry* entry : symbolEntries) {
		if (entry->name == name) {
			foundImpl = entry;
			break;
		}
	}
	return foundImpl;
}
SymbolTableEntry* SymbolTable::findVarOrParRec(std::string name) {
	if (SymbolTableEntry* parRec = findParRec(name)) {
		return parRec;
	}
	else if (SymbolTableEntry* varRec = findVariableRec(name)) {
		return varRec;
	}
	else return nullptr;
}



int SymbolTable::compOffset() {
	return 0;
}

int SymbolTable::compSize() {
	return 0;
}

std::string SymbolTable::toDot()
{
	std::stringstream currentTable;

	currentTable << "\"" + name + "\"" + " [label=<\n"
		<< "<TABLE BORDER = \"0\" CELLBORDER = \"1\" CELLSPACING = \"0\">\n"
		<< "<TR><TD COLSPAN = \"4\">" + name + "</TD></TR>\n"
		<< "<TR><TD>Name</TD><TD>Kind</TD><TD>Type</TD><TD>Link</TD></TR>\n";

	std::stringstream other;

	for (SymbolTableEntry* entry : table) {
		if (entry != nullptr) {
			currentTable << entry->toDot();
			if (entry->link && (dynamic_cast<ClassEntry*>(entry) || dynamic_cast<FunctionEntry*>(entry)||dynamic_cast<ImplementationEntry*>(entry))) {
				other << entry->link->toDot();
				other << "\"" << name << "\"" << ":\"" << entry->toStr() << "\"->\"" << entry->link->name << "\"\n";
			}
		}
		else {
			other << "ERROR";
		}
	}

	currentTable << "</TABLE>>];\n";
	currentTable << other.str();

	return currentTable.str();
}