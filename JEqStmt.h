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
        int run(std::set<Variable*>&, Ui::MainWindow*&, QMainWindow*, std::vector<std::pair<Identifier*,int>>*);
	std::string toString();
};

#endif
