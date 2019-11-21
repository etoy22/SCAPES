#ifndef DECLINTSTMT_HEADER
#define DECLINTSTMT_HEADER

#include <iostream>
#include <set> 
#include "Variable.h"
#include "Statement.h"

class DeclIntStmt : public Statement {

private:
protected:
public:
	DeclIntStmt();
    	~DeclIntStmt();
   	virtual void compile(std::string);
	void run();
	void run(std::set<Variable*>&);
	void run(std::set<Variable*>&, Ui::MainWindow*&, QMainWindow*);
	std::string toString();
};

#endif
