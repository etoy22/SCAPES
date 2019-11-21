#ifndef PROGRAM_HEADER
#define PROGRAM_HEADER

#include <iostream>
#include <string>
#include <vector>
#include <set> 
#include <sstream>
#include <QVariant>
#include "Statement.h"
#include "Identifier.h"
#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include "ui_mainwindow.h"
#include <QMainWindow>

class Program {
private:

	int comparisonFlag;
    std::string fileName;
    std::vector<std::string> input;
    std::vector<Statement*> statements;
    std::vector<std::pair<Identifier*,int>> pairs;
    std::set<Variable*> variables;
    QJsonArray out;
    QJsonObject program;
    Ui::MainWindow* ui;
    QMainWindow* win;
    bool checkSyntax();

protected:


	Identifier *identify;
	int identifySize;

public:

    // constructor
    Program(std::string, std::vector<std::string>&);
    Program(std::string, QJsonObject&);
	Program(QJsonObject&);
	~Program();

	//Executables
    bool compile();
	void execute();
	void print();
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
    

	// getters and setters
	std::string getFileName();
	int getComparisonFlag();
	void setName(std::string);
	void setUIPointer(Ui::MainWindow&);
	void setWindowPointer(QMainWindow*);
};
#endif
