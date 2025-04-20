#include "TempEntry.h"

TempEntry::TempEntry() {

}

std::string TempEntry::toStr() {
	return "Parameter: " + name + " " + type;
}

std::string TempEntry::toDot() {
	return "<TR><TD>" + name + "</TD><TD>temporary variable</TD><TD>" + type + "</TD><TD>" + std::to_string(compSize()) + "</TD><TD>" + std::to_string(offset) + "</TD><TD PORT=\"" + "tempvar-" + name + type + "\">/</TD></TR>\n";
}

int TempEntry::compSize() {
	int baseSize = 0;

	if (type == "int") {
		baseSize = 4;
	}
	else if (type == "float") {
		baseSize = 8;
	}
	else {
		if (link != nullptr) {
			baseSize = link->compSize();
		}
	}
	return baseSize;
}