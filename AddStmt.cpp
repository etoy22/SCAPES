#include <iostream>
#include <string>
#include <regex>
#include "AddStmt.h"
#include "Variable.h"

AddStmt::AddStmt() {
	label = new Label();
	label->setName("add");
	numOperands = 0;
	operands = new Operand * [2];
};

AddStmt::~AddStmt() {
	if (label != nullptr) {
		delete label;
	}
	if (operands != nullptr) {
		for (int i = 0; i < numOperands; i++) {
			if (operands[i] != nullptr) {
				delete operands[i];
			}
		}
		delete[] operands;
	}
	numOperands = 0;
};

void AddStmt::compile(std::string instr) {
	// remove consecutive spaces
	instr = removeConsecutiveSpaces(instr);

	// create regex to compare against instruction argument
	std::regex addRegex("(([\\s]?([^\\s])+([\\s]?): )?)([\\s])?add [^\\s]+[\\s][^\\s]+([\\s])?");

	// if instruction argument matches the above regex
	if (std::regex_match(instr, addRegex)) {

		// removes characters until command
		instr = removeLabelIfExists(instr);

		// TODO: retreive reference(s) (if applicable) of value(s)
		// remove "cmp" string from instruction
		if (!instr.empty()) {
			unsigned int index = instr.at(0) == ' ' ? 5 : 4;
			instr = instr.substr(index, instr.length());
		}

		// retrieve variable string names
		std::string variableName1 = removeSpaces(instr.substr(0, instr.find(" ")));
		std::string variableName2 = removeSpaces(instr.substr(instr.find(" ") + 1, instr.length()));

		// create variable from instruction argument
		operands[numOperands++] = new Operand();
		operands[0]->setIdentifier(new Variable(variableName1));
		operands[numOperands++] = new Operand();
		operands[1]->setIdentifier(new Variable(variableName2));
	}
  
}

int AddStmt::run(std::set<Variable*>& variableSet, IOInterface*, std::vector<std::pair<Identifier*,int>>*){

	int values[2];

	if (operands[0]->getIdentifier() != nullptr && operands[1]->getIdentifier() != nullptr) {
		std::regex numRegex("[\\d]+");

		for (unsigned int i = 0; i < 2; i++) {
			if (std::regex_match(operands[i]->getIdentifier()->getName(), numRegex)) {
				values[i] = std::stoi(operands[i]->getIdentifier()->getName());
			}
			else {
				try {
					Variable* result = getVariable(variableSet, operands[i]->getIdentifier()->getName());
					if (result != nullptr) {
						values[i] = result->getValue();

						if (i == 1) {
							std::cout << "Before Add: " + std::to_string(result->getValue()) << std::endl;
							result->setValue(values[0] + values[1]);
							std::cout << "After Add: " + std::to_string(result->getValue()) << std::endl;
						}

					}
					else {
						throw std::string("Variable undefined");
					}
				}
				catch (std::string err) {
					throw err;
				}				
			}
		}
	}
    return  0;
}

std::string AddStmt::toString() {
	std::string output = "About the AddStmt object: <";

	if (label != nullptr) {
		output += label->toString();
	}
	else {
		output += "Instruction doesn't have label. ";
	}

	for (int i = 0; i < numOperands && operands != nullptr; i++) {
		output += " | " + operands[i]->toString();
	}

	output += ">";

	return output;
}
