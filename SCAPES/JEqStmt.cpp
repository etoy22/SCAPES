#include <iostream>
#include <string>
#include <regex>
#include "JEqStmt.h"


JEqStmt::JEqStmt() {
	label = new Label();
	label->setName("jeq");
	numOperands = 0;
	operands = new Operand * [1];
};

JEqStmt::~JEqStmt() {
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

void JEqStmt::compile(std::string instr) {

	// remove consecutive spaces
	instr = removeConsecutiveSpaces(instr);

	// create regex to compare against instruction argument
	std::regex jeqRegex("(([\\s]?([^\\s])+([\\s]?): )?)([\\s])?jeq [^\\s]+([\\s])?");

	// if instruction argument matches the above regex
	if (std::regex_match(instr, jeqRegex)) {

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

int JEqStmt::run(std::set<Variable*>&, IOInterface*, std::vector<std::pair<Identifier*,int>>*id){
    int result = -1;
    for(unsigned int i =0; i<id->size(); i++){
        if(id->at(i).first->getName()==this->getOperand(0)->getIdentifier()->getName())
            result = id->at(i).second;
    }
    return result-1;
}

std::string JEqStmt::toString() {
	std::string output = "About the JEqStmt object: <";

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
