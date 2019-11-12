#ifndef READSTMT_HEADER
#define READSTMT_HEADER

#include <iostream>
#include "Statement.h"

class ReadStmt : public Statement {
private:
protected:
public:
	ReadStmt();
    ~ReadStmt();

	void compile(std::string);
	void run();

	std::string toString();
};

#endif
