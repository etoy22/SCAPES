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
	void run();
	void run(std::set<Variable*>&);
        void run(std::set<Variable*>&, Ui::MainWindow*&, QMainWindow*);
	std::string toString();
};

#endif
