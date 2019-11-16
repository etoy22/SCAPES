#include <iostream>
#include "Operand.h"
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
    if(json.contains("Identifier") && json["Identifier"].isString()){
        identifier = new Identifier();
        identifier->read(json["Identifier"].toObject());
    }
}
void Operand::write(QJsonObject &json) const{
    QJsonObject id;
    if (identifier != nullptr){
        identifier->write(id);
    }
    json["Identifier"] = id;
}
