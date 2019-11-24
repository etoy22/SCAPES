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
	void run();
	void run(std::set<Variable*>&);
        void run(std::set<Variable*>&, Ui::MainWindow*&, QMainWindow*);
};

#endif
