#ifndef IDENTIFIER_HEADER
#define IDENTIFIER_HEADER

#include <iostream>
#include <string>
#include <QObject>

class Identifier{
    Q_GADGET
private:

protected:
	std::string name;

public:
	// constructors
	Identifier();
    Identifier(const Identifier&);
    Identifier operator=(const Identifier&);
    virtual ~Identifier();
	Identifier(std::string);

	// getters and setters - name
	std::string getName();
	void setName(std::string);
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

	virtual std::string toString() ;
};

#endif
