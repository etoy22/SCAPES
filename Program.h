#ifndef PROGRAM_HEADER
#define PROGRAM_HEADER

#include <iostream>
#include <string>
#include <vector>
#include<set> 
#include <sstream>
#include <QVariant>

#include "Identifier.h"
#include <QObject>
#include <QJsonArray>
#include <QJsonObject>

class Program {
private:

	int comparisonFlag;
    std::string fileName;
    std::vector<std::string> input;
    QJsonArray out;
    QJsonObject program;
    bool checkSyntax();

protected:


	Identifier *identify;
	int identifySize;

public:

	
	
	

    // constructor
    Program(std::string, std::vector<std::string>&);

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
	

};
#endif
