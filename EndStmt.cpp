#include <iostream>
#include <regex>
#include "EndStmt.h"

EndStmt::EndStmt() {
    label = new Label();
    label->setName("end");
    numOperands = 0;
    operands = nullptr;
}

EndStmt::~EndStmt(){
    numOperands = 0;
    if (label != nullptr){
        delete label;
    }
};

void EndStmt::compile(std::string instr) {

    // remove consecutive spaces
    instr = removeConsecutiveSpaces(instr);

    // create regex to compare against instruction argument
    std::regex endRegex("(([\\s]?([^\\s])+([\\s]?): )?)([\\s])?end([\\s])?");

}

void EndStmt::run() {
	// nothing yet
}
