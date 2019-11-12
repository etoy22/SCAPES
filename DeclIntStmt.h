#ifndef DECLINTSTMT_HEADER
#define DECLINTSTMT_HEADER

#include <iostream>
#include "Statement.h"

class DeclIntStmt : public Statement {

private:
protected:
public:
	DeclIntStmt();
    ~DeclIntStmt();
    virtual void compile(std::string);
	void run();

	std::string toString();
};

#endif
