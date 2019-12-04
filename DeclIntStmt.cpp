#include <iostream>
#include <string>
#include <regex>
#include "DeclIntStmt.h"
#include "Variable.h"

DeclIntStmt::DeclIntStmt() {
    label = new Label();
    label->setName("dci");
    numOperands = 0;
    operands = new Operand*[2];
};

DeclIntStmt::~DeclIntStmt() {
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

void DeclIntStmt::compile(std::string instr) {

    // remove consecutive spaces
    instr = removeConsecutiveSpaces(instr);

    // create regex to compare against instruction argument
    std::regex dciRegex("(([\\s]?([^\\s])+([\\s]?): )?)([\\s])?dci [^\\s]+([\\s])?");

    // if instruction argument matches the above regex
    if (std::regex_match(instr, dciRegex)) {

        // removes characters until command
        instr = removeLabelIfExists(instr);

        // remove dci from instruction
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

int DeclIntStmt::run(std::set<Variable*>& variableSet, Ui::MainWindow*& ui, QMainWindow* win, std::vector<std::pair<Identifier*,int>>* id) {
	bool variableExists = true;

	if (operands[0] != nullptr && operands[0]->getIdentifier() != nullptr) {
		try {	
			Variable* result = getVariable(variableSet, operands[0]->getIdentifier()->getName());
			if (result == nullptr) {
				variableExists = false;
			}
		}
		catch (std::string err) {
			throw err;
		}
		
	}

	if (!variableExists) {
		variableSet.insert((Variable*)operands[0]->getIdentifier());
	}

	return 0;
}

std::string DeclIntStmt::toString() {
    std::string output = "About the DeclIntStmt object: <";

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
