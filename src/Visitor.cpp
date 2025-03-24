#include "Visitor.h"

void Visitor::outError(std::string err, int line) {
	std::string str = "Line " + std::to_string(line) + ": " + err;
	errors.push_back(str);
}