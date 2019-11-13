#ifndef JEQSTMT_HEADER
#define JEQSTMT_HEADER

#include <iostream>
#include "Statement.h"

class JEqStmt : public Statement {

private:
protected:
public:
	  JEqStmt();
    ~JEqStmt();
    virtual void compile(std::string);
	  void run();

	std::string toString();
};

#endif
