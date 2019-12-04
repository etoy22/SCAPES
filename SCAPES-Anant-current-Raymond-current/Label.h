#ifndef LABEL_HEADER
#define LABEL_HEADER

#include <iostream>
#include <string>
#include "Identifier.h"

class Label : public Identifier {
private:
protected:
public:
	// constructors
	Label();
	Label(std::string);

    virtual std::string toString();
};

#endif
