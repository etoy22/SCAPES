#include <iostream>
#include <string>
#include <regex>
#include "DeclArrStmt.h"
#include "Variable.h"

DeclArrStmt::DeclArrStmt() {
	label = new Label();
	label->setName("dca");
	numOperands = 0;
	operands = nullptr;
};

DeclArrStmt::~DeclArrStmt() {
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

void DeclArrStmt::compile(std::string instr) {
	// remove consecutive spaces
	instr = removeConsecutiveSpaces(instr);

	// create regex to compare against instruction argument
	std::regex dcaRegex("(([\\s]?([^\\s])+([\\s]?): )?)([\\s])?dca [^\\s]+[\\s][\\d]+([\\s])?");

	// if instruction argument matches the above regex
	if (std::regex_match(instr, dcaRegex)) {

		// removes characters until command
		instr = removeLabelIfExists(instr);

		// TODO: retreive reference(s) (if applicable) of value(s)
		// remove "cmp" string from instruction
		if (!instr.empty()) {
			unsigned int index = instr.at(0) == ' ' ? 5 : 4;
			instr = instr.substr(index, instr.length());
		}

		// retrieve variable string names
		std::string variableName = removeSpaces(instr.substr(0, instr.find(" ")));
		int amount = std::stoi(removeSpaces(instr.substr(instr.find(" ") + 1, instr.length())));

		numOperands = 0;
		operands = new Operand*[amount];
		
		for (int i = 0; i < amount; i++) {
			operands[numOperands] = new Operand();
			operands[numOperands++]->setIdentifier(new Variable("$"+variableName+"+"+std::to_string(i)));
		}
	}
  
}

void DeclArrStmt::run() {
	// nothing yet
}

void DeclArrStmt::run(std::set<Variable*>& variableSet) {
	bool variableExists = true;

	for (int i = 0; i < numOperands; i++) {
		if (operands[i] != nullptr && operands[i]->getIdentifier() != nullptr) {
			std::set<Variable*>::iterator result = std::find_if(std::begin(variableSet), std::end(variableSet),
				[&](Variable* const& v) { return v->getName() == operands[i]->getIdentifier()->getName();  });

			if (result == variableSet.end()) {
				variableExists = false;
			}
		}

		if (!variableExists) {
			variableSet.insert((Variable*)operands[i]->getIdentifier());
		}
	}
}

std::string DeclArrStmt::toString() {
	std::string output = "About the DeclArrStmt object: <";

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
