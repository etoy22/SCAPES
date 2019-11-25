#ifndef JUMPSTMT_HEADER
#define JUMPSTMT_HEADER

#include <iostream>
#include "Statement.h"

class JumpStmt : public Statement {
private:
protected:
public:
	JumpStmt();
    	~JumpStmt();
    	virtual void compile(std::string);
        int run(std::set<Variable*>&, Ui::MainWindow*&, QMainWindow*, std::vector<std::pair<Identifier*,int>>*);
	std::string toString();
};

#endif
