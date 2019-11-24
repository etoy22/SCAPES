#ifndef PRINTSTMT_HEADER
#define PRINTSTMT_HEADER

#include <iostream>
#include "Statement.h"

class PrintStmt : public Statement {
private:
protected:
public:
	PrintStmt();
    ~PrintStmt();

	void compile(std::string);
	void run();
	void run(std::set<Variable*>&);
        void run(std::set<Variable*>&, Ui::MainWindow*&, QMainWindow*);
	std::string toString();
};

#endif
