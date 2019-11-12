#ifndef PRINTSTMT_HEADER
#define PRINTSTMT_HEADER

#include <iostream>
#include "Statement.h"

class PrintStmt : public Statement {
private:
protected:
public:
	PrintStmt();
    ~PrintStmt();

	void compile(std::string);
	void run();

	std::string toString();
};

#endif
