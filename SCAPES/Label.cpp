#include <iostream>
#include "Label.h"

Label::Label() {

}

Label::Label(std::string name) : Identifier(name) {
}

std::string Label::toString() {
	return "(Label) - " + name;
}
