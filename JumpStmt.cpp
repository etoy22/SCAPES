#include <iostream>
#include <regex>
#include "JumpStmt.h"

JumpStmt::JumpStmt() {
    label = new Label();
    label->setName("jmp");
    numOperands = 0;
    operands = new Operand * [1];
}

JumpStmt::~JumpStmt() {
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

void JumpStmt::compile(std::string instr) {

    // remove consecutive spaces
    instr = removeConsecutiveSpaces(instr);

    // create regex to compare against instruction argument
    std::regex jumpRegex("(([\\s]?([^\\s])+([\\s]?): )?)([\\s])?jmp [^\\s]+([\\s])?");

    // if instruction argument matches the above regex
    if (std::regex_match(instr, jumpRegex)) {

        // removes characters until command
        instr = removeLabelIfExists(instr);

        // remove jmp from instruction
        if (!instr.empty()) {
            unsigned int index = instr.at(0) == ' ' ? 5 : 4;
            instr = instr.substr(index, instr.length());
        }

        // create variable from instruction argument
        std::string variableName = removeSpaces(instr.substr(0, instr.length()));
        operands[0] = new Operand();
        operands[0]->setIdentifier(new Label(variableName));
        numOperands = 1;
    }
}

void JumpStmt::run() {
	// nothing yet
}

void JumpStmt::run(std::set<Variable*>&){}
void JumpStmt::run(std::set<Variable*>&, Ui::MainWindow*&, QMainWindow*){}


std::string JumpStmt::toString() {
    std::string output = "About the JumpStmt object: <";

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
