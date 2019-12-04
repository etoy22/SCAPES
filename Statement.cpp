#include <iostream>
#include <regex>
#include "Statement.h"

Statement::Statement() {
	numOperands = 0;

}

Statement::~Statement(){};

void Statement::setLabel(Label* labelParam) {
	label = labelParam;
}
void Statement::setOperand(Operand* operand, int index) {
	if (index < numOperands) {
		operands[index] = operand;
	}
}
void Statement::setNumOperands(int numOperandParam) {
	numOperands = numOperandParam;
}

Label* Statement::getLabel() {
	return label;
}
Operand* Statement::getOperand(int index) {
	if (index < numOperands) {
		return operands[index];
	}
    return nullptr;
}
int Statement::getNumOperands() {
	return numOperands;
}

 Operand** Statement::getOperands() {
    return operands;
}

 void Statement::read(const QJsonObject& json){
     if(json.contains("Label") && json["Label"].isString()){
         label = new Label();
         label->read(json["Label"].toObject());
     }

     if(json.contains("Operands") && json["Operands"].isArray()){
         QJsonArray ops = json["Operands"].toArray();
		 operands = new Operand* [ops.size()];
		 numOperands = ops.size();

         for(int i=0; i<ops.size(); i++){
            QJsonObject operandObj = ops[i].toObject();
            Operand* op = new Operand();
            op->read(operandObj);
            operands[i] = op;
         }
     }
 }

 void Statement::write(QJsonObject& json) const{
     QJsonObject lab;
     label->write(lab);
     json["Label"] = lab;

     if (numOperands !=0){
         QJsonArray ops;
         int i = 0;

         for (i =0; i<numOperands; i++){
             if (operands[i] != nullptr){
                 Operand* op = operands[i];
                 QJsonObject operand;
                 op->write(operand);
                 ops.append(operand);
             }
         }

         json["Operands"] = ops;
     }
 }

 std::string Statement::removeSpaces(std::string input) {
     std::regex space("[\\s]");

     return std::regex_replace(input, space, "");
 }

 std::string Statement::removeConsecutiveSpaces(std::string input) {
     std::regex whitespace("[\\s]+");
     return std::regex_replace(input, whitespace, " ");
 }

 std::string Statement::removeLabelIfExists(std::string instr){
     // if instruction contains label, remove it
     if (instr.find(':') != std::string::npos && instr.find(':') + 2 <= instr.length()) {
         // debugging: TODO: either comment or remove later
         std::cout << "//Instruction has label" << std::endl;

         // remove label from instruction
         return instr.substr(instr.find(':') + 2, instr.length());
     }
     return instr;
 }

 Variable* Statement::getVariable(std::set<Variable*> variableSet, std::string name) {
     std::regex digit("[\\d]+");
     std::regex arrayElement("\\$[^\\s]+\\+[^\\s]+");

     name = removeSpaces(name);

    if (std::regex_match(name, arrayElement)) {

        // extract index
        std::string varName = name.substr(name.find_last_of("+") + 1, name.length() - 1);

        // if index is literal (e.g. 4)
        if (std::regex_match(varName, digit)) {
            // find and return $<arr>+<literal>
            std::set<Variable*>::iterator result = std::find_if(std::begin(variableSet), std::end(variableSet),
                [&](Variable* const& v) { return v->getName() == name;  });
            
            if (result != variableSet.end()) {
                return (*result);
            }
        }
        // if index is variable
        else {
            // find variable
            std::set<Variable*>::iterator result = std::find_if(std::begin(variableSet), std::end(variableSet),
                [&](Variable* const& v) { return v->getName() == varName;  });

            // get value of variable + return associated array element
            if (result != variableSet.end()) {
                int value = (*result)->getValue();

                std::string varName2 = name.substr(0, name.find_last_of("+") + 1) + std::to_string(value);

                std::set<Variable*>::iterator variable = std::find_if(std::begin(variableSet), std::end(variableSet),
                    [&](Variable* const& v) { return v->getName() == varName2;  });

                if (variable != variableSet.end()) {
                    return (*variable);
                }
                else {
                    throw std::string("Index out of bounds");
                }
            }
            else {
                throw std::string("Variable not declared");
            }
        }
    }
    else if (!regex_match(name, arrayElement)) {

        std::set<Variable*>::iterator result = std::find_if(std::begin(variableSet), std::end(variableSet),
            [&](Variable* const& v) { return v->getName() == name;  });

        if (result != variableSet.end()) {
            return (*result);
        }
    }    

    return nullptr;
 }
 
 std::string Statement::toString() {
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
