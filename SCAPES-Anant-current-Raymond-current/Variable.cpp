#include <iostream>
#include <string>
#include "Variable.h"

Variable::Variable() {
	value = 0;
	name = "";
}

Variable::Variable(std::string nameParam) {
	name = nameParam;
	value = 0;
}

Variable::Variable(int valueParam) {
	value = valueParam;
	name = "";
}

Variable::Variable(std::string nameParam, int valueParam) {
	name = nameParam;
	value = valueParam;
}

void Variable::setValue(int valueParam) {
	value = valueParam;
}

int Variable::getValue() {
	return value;
}

std::string Variable::toString() {
	return "(Variable) - " + name + " : " + std::to_string(value);
}