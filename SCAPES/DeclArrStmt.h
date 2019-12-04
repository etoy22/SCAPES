#ifndef DECLARRSTMT_HEADER
#define DECLARRSTMT_HEADER

#include <iostream>
#include "Statement.h"
#include "IOInterface.h"

class DeclArrStmt : public Statement {

private:
protected:
public:
	DeclArrStmt();
        ~DeclArrStmt();
        virtual void compile(std::string);
        int run(std::set<Variable*>&, IOInterface*, std::vector<std::pair<Identifier*,int>>*);
	std::string toString();
};

#endif
