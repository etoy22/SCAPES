#ifndef STATEMENT_HEADER
#define STATEMENT_HEADER

#include <iostream>
#include <string>
#include <set>
#include "Label.h"
#include "Variable.h"
#include "Operand.h"
#include <QObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "ui_mainwindow.h"
#include <QMainWindow>
#include "IOInterface.h"


class Statement{
private:

protected:
    	Label *label;
    	Operand** operands;
    	int numOperands;

    	std::string removeSpaces(std::string);
    	std::string removeConsecutiveSpaces(std::string);
    	std::string removeLabelIfExists(std::string);
        Variable* getVariable(std::set<Variable*>, std::string);

public:
	// constructors
	Statement();
	virtual ~Statement();

	// class diagram methods
	virtual void compile(std::string) = 0;
	virtual int run(std::set<Variable*>&, IOInterface*, std::vector<std::pair<Identifier*,int>>*) = 0;
	
        void setLabel(Label*);

        void setOperand(Operand*, int);
	void setNumOperands(int);

    	void read(const QJsonObject &json);
    	void write(QJsonObject &json) const;

    	Label* getLabel();
        Operand* getOperand(int);
        Operand** getOperands();
	int getNumOperands();
	virtual std::string toString();
};

#endif
