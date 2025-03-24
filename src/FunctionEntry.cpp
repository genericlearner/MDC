#include "FunctionEntry.h"
#include <sstream>

FunctionEntry::FunctionEntry() {

}
std::string FunctionEntry::signString() {
	std::stringstream ss;

	for (std::tuple<std::string, std::string, std::vector<int>> param : paramList) {
		ss << std::get<0>(param);

		for (int arrInd : std::get<2>(param)) {
			if (arrInd == -1) {
				ss << "[]";
			}
			else {
				ss << "[" + std::to_string(arrInd) + "]";
			}
		}
		ss << ", ";
	}
	return ss.str();
}

bool FunctionEntry::compare(FunctionEntry* fEntry) {
	if (name == fEntry->name && returnType == fEntry->returnType && paramList.size() == fEntry->paramList.size()) {
		bool duplicate = true;
		for (int i = 0; i < paramList.size(); i++) {
			auto t1 = paramList[i];
			auto t2 = fEntry->paramList[i];

			if (!(std::get<0>(t1) == std::get<0>(t2) && std::get<2>(t1).size() == std::get<2>(t2).size())) {
				duplicate = false;
			}
		}
		return duplicate;
	}
	return false;
}

std::string FunctionEntry::toStr() {
	return "function :" + name + "-" + signString();
}
std::string FunctionEntry::toDot() {
	return "<TR><TD>" + name + "</TD><TD>function</TD><TD>" + returnType + ":" + signString()  + std::to_string(offset) + "</TD><TD PORT=\"" + "function-" + name + "-" + signString() + "\">+</TD></TR>\n";
}