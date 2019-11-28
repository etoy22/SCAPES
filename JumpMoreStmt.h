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
        int run(std::set<Variable*>&, Ui::MainWindow*&, QMainWindow*, std::vector<std::pair<Identifier*,int>>*);
	std::string toString();
};

#endif
