#include <iostream>
#include <string>
#include <regex>
#include "DeclIntStmt.h"
#include "Variable.h"

AddStmt::AddStmt() {
   
};

AddStmt::~AddStmt() {

};

void AddStmt::compile(std::string instr) {

  
}

void AddStmt::run() {
	// nothing yet
}

std::string AddStmt::toString() {
    std::string output = "About the DeclIntStmt object: <";


    return output;
}
