#ifndef DECLINTSTMT_HEADER
#define DECLINTSTMT_HEADER

#include <iostream>
#include <set> 
#include "Variable.h"
#include "Statement.h"
#include "IOInterface.h"

class DeclIntStmt : public Statement {

private:
protected:
public:
	DeclIntStmt();
    	~DeclIntStmt();
   	virtual void compile(std::string);
	int run(std::set<Variable*>&, IOInterface*, std::vector<std::pair<Identifier*,int>>*);
	std::string toString();
};

#endif
