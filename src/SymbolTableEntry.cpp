#include "SymbolTable.h"
#include "SymbolTableEntry.h"
SymbolTableEntry::SymbolTableEntry() {  
	this->link = nullptr;
}

int SymbolTableEntry::getOffset() {
	return offset;
}
