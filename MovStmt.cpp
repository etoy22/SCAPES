#include <iostream>
#include <string>
#include <regex>
#include "DeclIntStmt.h"
#include "Variable.h"

MovStmt::MovStmt() {
   
};

MovStmt::~MovStmt() {

};

void MovStmt::compile(std::string instr) {

  
}

void MovStmt::run() {
	// nothing yet
}

std::string MovStmt::toString() {
    std::string output = "About the MovStmt object: <";


    return output;
}
