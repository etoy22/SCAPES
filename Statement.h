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


class Statement{
private:

protected:
    Label *label;
    Operand** operands;
    int numOperands;

    std::string removeSpaces(std::string);
    std::string removeConsecutiveSpaces(std::string);
    std::string removeLabelIfExists(std::string);

public:
	// constructors
	Statement();
	virtual ~Statement();

	// class diagram methods
	virtual void compile(std::string) = 0;
	virtual void run() = 0;
	virtual void run(std::set<Variable*>&) = 0;
	virtual void run(std::set<Variable*>&, Ui::MainWindow*&, QMainWindow*) = 0;
	//virtual void run(std::set<Variable*>&);
	//virtual void run(std::set<Variable*>&, Ui::MainWindow*&);
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
