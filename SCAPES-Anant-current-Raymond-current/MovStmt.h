#ifndef MOVSTMT_HEADER
#define MOVSTMT_HEADER

#include <iostream>
#include "Statement.h"
#include "IOInterface.h"
#include "Variable.h"

class MovStmt : public Statement {

private:
protected:
public:
	MovStmt();
    	~MovStmt();
    	virtual void compile(std::string);
        int run(std::set<Variable*>&, IOInterface*, std::vector<std::pair<Identifier*,int>>*);
	std::string toString();
};

#endif
