#include "VariableEntry.h"
#include <sstream>

std::string VariableEntry::generateSign() {
	std::stringstream ss;

	ss << type;

	for (int arrayIndice : arrayDimension) {
		if (arrayIndice == -1) {
			ss << "[]";
		}
		else {
			ss << "[" + std::to_string(arrayIndice) + "]";
		}
	}
	return ss.str();
}

VariableEntry::VariableEntry() {

}

std::string VariableEntry::toStr() {
	return "Variable- " + generateSign();
}

std::string VariableEntry::toDot() {
	return "<TR><TD>" + name + "</TD><TD>variable</TD><TD>" + generateSign() + "</TD><TD>" + std::to_string(compSize()) + "</TD><TD>" + std::to_string(offset) + "</TD><TD PORT=\"" + "variable-" + generateSign() + "\">/</TD></TR>\n";
}

int VariableEntry::compSize() {
	int bSize = 0;
	if (type == "int") {
		bSize = 4;
	}
	else if (type == "float") {
		bSize = 8;
	}
	else {
		if (link != nullptr) {
			bSize = link->compSize();
		}
	}
	int arrElements = 1;
	for (int size : arrayDimension) {
		if (size == -1) {
			continue;
		}
		arrElements *= size;
	}
	return bSize * arrElements;
}