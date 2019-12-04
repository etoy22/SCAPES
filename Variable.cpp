#include <iostream>
#include <string>
#include <random>
#include "Variable.h"

Variable::Variable() {
	std::default_random_engine generator(std::random_device{}());
	std::uniform_int_distribution<int> distribution(0,INT_MAX - 1);

	value = distribution(generator);
	name = "";
}

Variable::Variable(std::string nameParam) {
	std::default_random_engine generator(std::random_device{}());
	std::uniform_int_distribution<int> distribution(0,INT_MAX - 1);
	
	name = nameParam;
	value = distribution(generator);
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