#ifndef DECLARRSTMT_HEADER
#define DECLARRSTMT_HEADER

#include <iostream>
#include "Statement.h"

class DeclArrStmt : public Statement {

private:
protected:
public:
	DeclArrStmt();
        ~DeclArrStmt();
        virtual void compile(std::string);
        int run(std::set<Variable*>&, Ui::MainWindow*&, QMainWindow*, std::vector<std::pair<Identifier*,int>>*);
	std::string toString();
};

#endif
