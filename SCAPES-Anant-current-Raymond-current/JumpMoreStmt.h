#ifndef JUMPMORESTMT_HEADER
#define JUMPMORESTMT_HEADER

#include <iostream>
#include "Statement.h"
#include "Variable.h"
#include "IOInterface.h"

class JumpMoreStmt : public Statement {
private:
protected:
public:
	JumpMoreStmt();
    	~JumpMoreStmt();
    	virtual void compile(std::string);
        int run(std::set<Variable*>&, IOInterface*, std::vector<std::pair<Identifier*,int>>*);
	std::string toString();
};

#endif
