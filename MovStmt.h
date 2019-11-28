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
        int run(std::set<Variable*>&, Ui::MainWindow*&, QMainWindow*, std::vector<std::pair<Identifier*,int>>*);
	std::string toString();
};

#endif
