#ifndef COMPSTMT_HEADER
#define COMPSTMT_HEADER

#include <iostream>
#include "Statement.h"

class CompStmt : public Statement {


private:
protected:
public:
	CompStmt();
    ~CompStmt();

	virtual void compile(std::string);
	void run();

	std::string toString();
};

#endif
