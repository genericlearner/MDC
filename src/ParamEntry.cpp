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
	return "<TR><TD>" + name + "</TD><TD>parameter</TD><TD>" + generateSign() + "</TD><TD PORT=\"" + "parameter-" + generateSign() + "\">/</TD></TR>\n";
}

int ParamEntry::compSize() {
	return 0;
}

