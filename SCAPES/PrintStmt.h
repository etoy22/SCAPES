#ifndef PRINTSTMT_HEADER
#define PRINTSTMT_HEADER

#include <iostream>
#include "Statement.h"
#include "IOInterface.h"

class PrintStmt : public Statement {
private:
protected:
public:
	PrintStmt();
    	~PrintStmt();
	void compile(std::string);
        int run(std::set<Variable*>&, IOInterface*, std::vector<std::pair<Identifier*,int>>*);
	std::string toString();
};

#endif
