#include "ParamEntry.h"
#include <sstream>

ParamEntry::ParamEntry() {

}

std::string ParamEntry::generateSign() {
	std::stringstream ss;

	ss << type;

	for (int arrIndice : arrInd) {
		if (arrIndice == -1) {
			ss << "[]";
		}
		else {
			ss << "[" + std::to_string(arrIndice) + "]";
		}
	}
	return ss.str();
}

std::string ParamEntry::toStr() {
	return "parameter: " + generateSign();
}

std::string ParamEntry::toDot() {
	return "<TR><TD>" + name + "</TD><TD>parameter</TD><TD>" + generateSign() + "</TD><TD>" + std::to_string(compSize()) + "</TD><TD>" + std::to_string(offset) + "</TD><TD PORT=\"" + "parameter-" + generateSign() + "\">/</TD></TR>\n";
}

int ParamEntry::compSize() {
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

	int arrElmt = 1;

	for (auto size : arrInd) {
		if (size == -1) {
			continue;
		}
		arrElmt *= size;
	}
	return bSize * arrElmt;
}

