#ifndef ADDSTMT_HEADER
#define ADDSTMT_HEADER

#include <iostream>
#include "Statement.h"

class AddStmt : public Statement {

private:
protected:
public:
	AddStmt();
    ~AddStmt();
    virtual void compile(std::string);
	void run();

	std::string toString();
};

#endif
