#ifndef COMPSTMT_HEADER
#define COMPSTMT_HEADER

#include <iostream>
#include "Statement.h"
#include "IOInterface.h"

class CompStmt : public Statement {


private:
    bool isNumber(std::string);
protected:
public:
	CompStmt();
    ~CompStmt();

	virtual void compile(std::string);
    int run(std::set<Variable*>&, IOInterface*, std::vector<std::pair<Identifier*,int>>*);
	std::string toString();
};

#endif
