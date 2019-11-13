#include <iostream>
#include <string>
#include <regex>
#include "DeclIntStmt.h"
#include "Variable.h"

DeclArrStmt::DeclArrStmt() {
   
};

DeclArrStmt::~DeclArrStmt() {

};

void DeclArrStmt::compile(std::string instr) {

  
}

void DeclArrStmt::run() {
	// nothing yet
}

std::string DeclArrStmt::toString() {
    std::string output = "About the DeclArrStmt object: <";


    return output;
}
