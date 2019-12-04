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
		std::string amount = removeSpaces(instr.substr(instr.find(" ") + 1, instr.length()));

		numOperands = 2;
		operands = new Operand*[numOperands];

		operands[0] = new Operand();
		operands[0]->setIdentifier(new Variable(variableName));

		operands[1] = new Operand();
		operands[1]->setIdentifier(new Variable(amount));
	}
}

int DeclArrStmt::run(std::set<Variable*>& variableSet, IOInterface*, std::vector<std::pair<Identifier*,int>>* id) {
	bool variableExists = true;
	int size = 0;
	std::regex digit("[\\d]+");

	if (operands[0] != nullptr && operands[0]->getIdentifier() != nullptr
		&& operands[1] != nullptr && operands[1]->getIdentifier() != nullptr) {

		// if size is a literal
		if (std::regex_match(operands[1]->getIdentifier()->getName(), digit)) {
			size = std::stoi(operands[1]->getIdentifier()->getName());
		}
		// otherwise size is stored in a variable
		else {
			try {
				Variable* result = getVariable(variableSet, operands[1]->getIdentifier()->getName());
				if (result != nullptr) {
					size = result->getValue();
				}
				else {
					throw "Variable not declared";
				}
			}
			catch (std::string err) {
				throw err;
			}
		}

		std::string arrName = "$" + operands[0]->getIdentifier()->getName() + "+";
		for (int i = 0; i < size; i++) {
			try {
				Variable* result = getVariable(variableSet, arrName + std::to_string(i));
				if (result == nullptr) {
					variableExists = false;
				}

				if (!variableExists) {
					variableSet.insert(new Variable(arrName + std::to_string(i)));
				}
			}
			catch (std::string err) {
				throw err;
			}			
		}
	}
	
	return 0;
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
