#ifndef JLESSSTMT_HEADER
#define JLESSSTMT_HEADER

#include <iostream>
#include "Statement.h"

class JLessStmt : public Statement {

private:
protected:
public:
	  JLessStmt();
    ~JLessStmt();
    virtual void compile(std::string);
	void run();

	std::string toString();
};

#endif
