#ifndef READSTMT_HEADER
#define READSTMT_HEADER

#include <iostream>
#include "Statement.h"

class ReadStmt : public Statement {
private:
protected:
public:
	ReadStmt();
    ~ReadStmt();

	void compile(std::string);
	void run();
	void run(std::set<Variable*>&);
	void run(std::set<Variable*>&, Ui::MainWindow*&, QMainWindow*);

	std::string toString();
};

#endif
