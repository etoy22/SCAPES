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

// return value sets comparison flag in Program.cpp -> execute()
// return 0 if operands are equal
// return 1 if operand[0] < operand[1]
// return 2 if operand[0] > operand{1]
int CompStmt::run(std::set<Variable*>& variableSet, Ui::MainWindow*&, QMainWindow*, std::vector<std::pair<Identifier*,int>>*){

    int valueOne ; int valueTwo ;

       std::set<Variable*>::iterator result = std::find_if(std::begin(variableSet), std::end(variableSet),
               [&](Variable* const& v) { return v->getName() == operands[0]->getIdentifier()->getName();  });
       if (result != variableSet.end()) {
           valueOne = (*result)->getValue();
       }

        std::set<Variable*>::iterator result2 = std::find_if(std::begin(variableSet), std::end(variableSet),
                [&](Variable* const& v) { return v->getName() == operands[1]->getIdentifier()->getName();  });
        if (result2 != variableSet.end()) {
            valueTwo = (*result2)->getValue();
        }
	std::cout << "V1: " << valueOne << std::endl;
	std::cout << "V2: " << valueTwo << std::endl;
    if(valueOne == valueTwo)
        return 0;
    else if(valueOne < valueTwo)
        return 1;
    else
        return 2;
}


bool CompStmt::isNumber(std::string str){
    for (int i = 0; i < str.length(); i++)
       if (std::isdigit(str[i]) == false)
          return false;
    return true;
}


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
