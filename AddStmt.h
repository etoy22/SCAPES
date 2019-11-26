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
        int run(std::set<Variable*>&, Ui::MainWindow*&, QMainWindow*, std::vector<std::pair<Identifier*,int>>*);
	std::string toString();
};

#endif
