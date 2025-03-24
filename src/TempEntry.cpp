#include "TempEntry.h"

TempEntry::TempEntry() {

}

std::string TempEntry::toStr() {
	return "Parameter: " + name + " " + type;
}

std::string TempEntry::toDot() {
	return "<TR><TD>" + name + "</TD><TD>temp var</TD><TD>" + type + "</TD><TD>" + std::to_string(compSize()) + "</TD><TD>" + std::to_string(offset) + "</TD><TD PORT=\"" + "tempvar-" + name + type + "\">/</TD></TR>\n";
}

int TempEntry::compSize() {
	return 0;
}