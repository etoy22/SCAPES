#ifndef OPERAND_HEADER
#define OPERAND_HEADER

#include <iostream>
#include "Identifier.h"
#include <QObject>
#include <QJsonObject>

class Operand{
private:
    Identifier* identifier;

protected:
public:
	Operand();
    Operand(const Operand&);
    ~Operand();
    Operand operator=(const Operand&);
    Operand(Identifier*);

    void setIdentifier(Identifier*);
    Identifier* getIdentifier();
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

	std::string toString();
};

#endif
