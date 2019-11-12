#ifndef STATEMENT_HEADER
#define STATEMENT_HEADER

#include <iostream>
#include <string>
#include "Label.h"
#include "Operand.h"
#include <QObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

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

    void setLabel(Label*);

    void setOperand(Operand*, int);
	void setNumOperands(int);

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    Label* getLabel();
    Operand* getOperand(int);
    Operand** getOperands();
	int getNumOperands();

};

#endif
