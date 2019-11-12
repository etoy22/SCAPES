#include <iostream>
#include <regex>
#include "Variable.h"
#include "ReadStmt.h"

ReadStmt::ReadStmt() {
    label = new Label();
    label->setName("rdi");
    numOperands = 0;
    operands = new Operand * [1];
}

ReadStmt::~ReadStmt() {
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

void ReadStmt::compile(std::string instr) {

    // remove consecutive spaces
    instr = removeConsecutiveSpaces(instr);

    // create regex to compare against instruction argument
    std::regex rdiRegex("(([\\s]?([^\\s])+([\\s]?): )?)([\\s])?rdi [^\\s]+([\\s])?");

    // if instruction argument matches the above regex
    if (std::regex_match(instr, rdiRegex)) {

        // removes characters until command
        instr = removeLabelIfExists(instr);

        // remove rdi from instruction
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

void ReadStmt::run() {
	// nothing yet
}

std::string ReadStmt::toString() {
    std::string output = "About the ReadStmt object: <";

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
