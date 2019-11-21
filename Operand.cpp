#include <iostream>
#include <typeinfo>
#include "Operand.h"
#include "Variable.h"
#include "Label.h"
#include "Identifier.h"

Operand::Operand() {
    identifier = nullptr;
}

Operand::~Operand() {
    if (identifier != nullptr) {
        delete identifier;
    }
}

Operand::Operand(Identifier* identifierParam) {
	setIdentifier(identifierParam);
}

Operand::Operand(const Operand& operand){
    this->setIdentifier(operand.identifier);
};

Operand Operand::operator=(const Operand& operand){
    this->setIdentifier(operand.identifier);
    return *this;
};

void Operand::setIdentifier(Identifier* identifierParam) {
    identifier = identifierParam;
}

Identifier* Operand::getIdentifier() {
	return identifier;
}

std::string Operand::toString(){
    return "(Operand) - " + identifier->toString();
}


void Operand::read(const QJsonObject &json){
    if(json.contains("Identifier") ){
        identifier = new Identifier();
        identifier->read(json["Identifier"].toObject());
    }
	else if (json.contains("Variable")) {
		identifier = new Variable();
		identifier->read(json["Variable"].toObject());
	}
	else  if (json.contains("Label")) {
		identifier = new Label();
		identifier->read(json["Label"].toObject());
	}
}
void Operand::write(QJsonObject &json) const{
    QJsonObject id;

    if (identifier != nullptr){
        identifier->write(id);
    }
	
	if (typeid(*identifier) == typeid(Variable)) {
		json["Variable"] = id;
	}
	else if (typeid(*identifier) == typeid(Label)) {
		json["Label"] = id;
	}
	else {
		json["Identifier"] = id;
	}

    
}
