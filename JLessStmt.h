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
        int run(std::set<Variable*>&, Ui::MainWindow*&, QMainWindow*, std::vector<std::pair<Identifier*,int>>*);
	std::string toString();
};

#endif
