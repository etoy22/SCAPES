#include <iostream>
#include <regex>
#include <QInputDialog>
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

void ReadStmt::run(){}
void ReadStmt::run(std::set<Variable*>&){}

void ReadStmt::run(std::set<Variable*>& variableSet, Ui::MainWindow*& ui, QMainWindow* window) {
	int input = QInputDialog::getInt(window, "variable input", "enter a number");
	 if (operands[0] != nullptr && operands[0]->getIdentifier() != nullptr) {
                std::set<Variable*>::iterator result = std::find_if(std::begin(variableSet), std::end(variableSet),
                        [&](Variable* const& v) { return v->getName() == operands[0]->getIdentifier()->getName();  });

                if (result != variableSet.end()) {
                        (*result)->setValue(input);
                }
        }

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
