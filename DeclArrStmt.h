#ifndef DECLARRSTMT_HEADER
#define DECLARRSTMT_HEADER

#include <iostream>
#include "Statement.h"

class DeclArrStmt : public Statement {

private:
protected:
public:
	DeclArrStmt();
    ~DeclArrStmt();
    virtual void compile(std::string);
	void run();
	void run(std::set<Variable*>&);

	std::string toString();
};

#endif
