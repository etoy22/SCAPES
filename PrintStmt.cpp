#include <iostream>
#include <regex>
#include "Variable.h"
#include "PrintStmt.h"

PrintStmt::PrintStmt() {
    label = new Label();
    label->setName("prt");
    numOperands = 0;
    operands = new Operand * [1];
}

PrintStmt::~PrintStmt() {
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
}

void PrintStmt::compile(std::string instr) {
	// create regex to compare against instruction argument - no string argument but <var>
	std::regex prtRegex("(([\\s]+?([^\\s])+([\\s]+?): )?)([\\s]+)?prt[\\s]+[^\\s]+([\\s]+)?");

	// create regex to compare against instruction argument - with string argument "<str>"
	std::regex prtStrRegex("(([\\s]+?([^\\s])+([\\s]+?): )?)([\\s]+)?prt[\\s]+\"([\\s]+)?.+([\\s]+)?\"([\\s]+)?");

	// if instruction argument matches the above regex
	if (std::regex_match(instr, prtStrRegex)) {
		// create variable from instruction argument
		int strLength = instr.find_last_of("\"") - instr.find_first_of("\"") - 1;
		std::string variableName = instr.substr(instr.find_first_of("\"") + 1, strLength);

		operands[0] = new Operand();
		operands[0]->setIdentifier(new Variable(variableName));
		numOperands = 1;
	}
	else if (std::regex_match(instr, prtRegex)) {
		// remove consecutive spaces
		instr = removeConsecutiveSpaces(instr);

		// removes characters until command
		instr = removeLabelIfExists(instr);

		// remove prt from instruction
		if (!instr.empty()) {
			unsigned int index = instr.at(0) == ' ' ? 5 : 4;
			instr = instr.substr(index, instr.length());
		}

		// create variable from instruction argument
		std::string variableName = removeSpaces(instr.substr(0, instr.length()));
		operands[0] = new Operand();
		operands[0]->setIdentifier(new Variable(variableName));
		numOperands = 1;
	}
}


int PrintStmt::run(std::set<Variable*>& variableSet, IOInterface* io, std::vector<std::pair<Identifier*,int>>*){
	bool isLiteral = true;
	if (operands[0] != nullptr && operands[0]->getIdentifier() != nullptr) {
				try {
					Variable* result = getVariable(variableSet, operands[0]->getIdentifier()->getName());
					if (result != nullptr) {   //is a variable operand 
						isLiteral = false;
						io->displayProgramOutput(QString::number(result->getValue()));
					}
				}
				catch (std::string err) {
					throw err;
				}
        }
	if(isLiteral){
        io->displayProgramOutput(QString::fromStdString(this->getOperand(0)->getIdentifier()->getName()));
	}
	return 0;
}


std::string PrintStmt::toString() {
    std::string output = "About the PrintStmt object: <";

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
