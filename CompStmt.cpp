#include <iostream>
#include <regex>
#include "CompStmt.h"
#include "Variable.h"

CompStmt::CompStmt() {
    label = new Label();
    label->setName("cmp");
    numOperands = 0;
    operands = new Operand*[2];
}
CompStmt::~CompStmt() {    
    if (label != nullptr){
        delete label;
    }
    if (operands != nullptr){
		for (int i = 0; i < numOperands; i++) {
			if (operands[i] != nullptr) {
				delete operands[i];
			}
		}
        delete[] operands;
    }
	numOperands = 0;
}
void CompStmt::compile(std::string instr) {

    // remove consecutive spaces
    instr = removeConsecutiveSpaces(instr);

    // create regex to compare against instruction argument
    std::regex cmpRegex("(([\\s]?([^\\s])+([\\s]?): )?)([\\s])?cmp [^\\s]+[\\s][^\\s]+([\\s])?");

    // if instruction argument matches the above regex
    if (std::regex_match(instr, cmpRegex)) {

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

void CompStmt::run() {
	// nothing yet
}

void CompStmt::run(std::set<Variable*>& variableSet){
	/*/std::set<Variable*>::iterator result = std::find_if(std::begin(variableSet), std::end(variableSet),
		[&](Variable* const& v) { return v->getName() == operands[i]->getIdentifier()->getName();  });
		*/

	int values[2];

	if (operands[0]->getIdentifier() != nullptr && operands[1]->getIdentifier() != nullptr) {
		std::regex numRegex("[\\d]+");

		for (unsigned int i = 0; i < 2; i++) {
			if (std::regex_match(operands[i]->getIdentifier()->getName(), numRegex)) {
				values[i] = std::stoi(operands[i]->getIdentifier()->getName());
			}
			else {
				std::set<Variable*>::iterator result = std::find_if(std::begin(variableSet), std::end(variableSet),
					[&](Variable* const& v) { return v->getName() == operands[i]->getIdentifier()->getName();  });
				
				if (result != variableSet.end()) {
					values[i] = (*result)->getValue();
				}
				else {
					throw "Variable undefined";
				}
			}
		}

		std::cout << std::endl;
		std::cout << "Difference between : " + std::to_string(values[0] - values[1]) << std::endl;

	}
}

void CompStmt::run(std::set<Variable*>&, Ui::MainWindow*&, QMainWindow*){}


std::string CompStmt::toString() {
    std::string output = "About the CompStmt object: <";

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
