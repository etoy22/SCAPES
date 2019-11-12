#ifndef JUMPMORESTMT_HEADER
#define JUMPMORESTMT_HEADER

#include <iostream>
#include "Statement.h"

class JumpMoreStmt : public Statement {
private:
protected:
public:
	JumpMoreStmt();
    ~JumpMoreStmt();

    virtual void compile(std::string);
	void run();

	std::string toString();
};

#endif
