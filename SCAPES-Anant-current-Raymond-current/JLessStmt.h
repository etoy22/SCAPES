#ifndef JLESSSTMT_HEADER
#define JLESSSTMT_HEADER

#include <iostream>
#include "Statement.h"
#include "Variable.h"
#include "IOInterface.h"

class JLessStmt : public Statement {

private:
protected:
public:
	JLessStmt();
    	~JLessStmt();
    	virtual void compile(std::string);
        int run(std::set<Variable*>&, IOInterface*, std::vector<std::pair<Identifier*,int>>*);
	std::string toString();
};

#endif
