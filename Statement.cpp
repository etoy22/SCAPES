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

         for(int i=0; i<ops.size(); i++){
            QJsonObject operandObj = ops[i].toObject();
            Operand* op = new Operand();
            op->read(operandObj);
            operands[i] = op;
            numOperands = i;
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
