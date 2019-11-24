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
	void run();
	void run(std::set<Variable*>&);
        void run(std::set<Variable*>&, Ui::MainWindow*&, QMainWindow*);
	std::string toString();
};

#endif
