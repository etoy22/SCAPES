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
	void run();
	void run(std::set<Variable*>&);
        void run(std::set<Variable*>&, Ui::MainWindow*&, QMainWindow*);
	std::string toString();
};

#endif
