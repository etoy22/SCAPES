#ifndef VARIABLE_HEADER
#define VARIABLE_HEADER

#include <iostream>
#include "Identifier.h"

class Variable : public Identifier {
private:
	int value;

protected:
public:
	Variable();
	Variable(std::string);
	Variable(int);
	Variable(std::string, int);

	void setValue(int);
	int getValue();

    virtual std::string toString();
};

#endif
