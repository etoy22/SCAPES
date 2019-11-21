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
	void run();
	void run(std::set<Variable*>&);
        void run(std::set<Variable*>&, Ui::MainWindow*&, QMainWindow*);
	std::string toString();
};

#endif
