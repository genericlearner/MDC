#include "ClassEntry.h"

ClassEntry::ClassEntry() {

}

std::string ClassEntry::toStr() {
	return "class-" + name;
}

std::string ClassEntry::toDot() {
	return "<TR><TD>" + name + "</TD><TD>class</TD><TD></TD><TD>" + std::to_string(compSize()) + "</TD><TD>" + std::to_string(offset) + "</TD><TD PORT=\"" + "class-" + name + "\">+</TD></TR>\n";
}

int ClassEntry::compSize() {
	int bsize = 0;

	if (link != nullptr) {
		bsize = link->compSize();

	}
	return bsize;
}