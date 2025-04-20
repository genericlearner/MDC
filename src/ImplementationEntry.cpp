#include "ImplementationEntry.h"

ImplementationEntry::ImplementationEntry() {

}

std::string ImplementationEntry::toStr() {
	return "implementation-" + name;
}

std::string ImplementationEntry::toDot() {
	return "<TR><TD>" + name + "</TD><TD>class</TD><TD></TD><TD>" + std::to_string(compSize()) + "</TD><TD>" + std::to_string(offset) + "</TD><TD PORT=\"" + "implementation-" + name + "\">+</TD></TR>\n";
}

int ImplementationEntry::compSize() {
	int bsize = 0;

	if (link != nullptr) {
		bsize = link->compSize();

	}
	return bsize;
}