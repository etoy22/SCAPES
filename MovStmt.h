#ifndef MOVSTMT_HEADER
#define MOVSTMT_HEADER

#include <iostream>
#include "Statement.h"

class MovStmt : public Statement {

private:
protected:
public:
	MovStmt();
    ~MovStmt();
    virtual void compile(std::string);
	void run();

	std::string toString();
};

#endif
