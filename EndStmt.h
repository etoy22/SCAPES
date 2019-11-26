#ifndef ENDSTMT_HEADER
#define ENDSTMT_HEADER

#include <iostream>
#include "Statement.h"

class EndStmt : public Statement {
private:
protected:
public:
	EndStmt();
    	virtual ~EndStmt();
	virtual void compile(std::string);
        int run(std::set<Variable*>&, Ui::MainWindow*&, QMainWindow*, std::vector<std::pair<Identifier*,int>>*);
};

#endif
