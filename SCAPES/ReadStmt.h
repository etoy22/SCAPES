#ifndef READSTMT_HEADER
#define READSTMT_HEADER

#include <iostream>
#include "Statement.h"
#include "Variable.h"
#include "IOInterface.h"

class ReadStmt : public Statement {
private:
protected:
public:
	ReadStmt();
    	~ReadStmt();
	void compile(std::string);
	int run(std::set<Variable*>&, IOInterface*, std::vector<std::pair<Identifier*,int>>*);
	std::string toString();
};

#endif
