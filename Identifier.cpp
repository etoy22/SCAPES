
#include "Identifier.h"
#include <QJsonObject>

Identifier::Identifier(){
}

Identifier::Identifier(const Identifier& obj){
    this->setName(obj.name);
};

Identifier Identifier::operator=(const Identifier& obj){
    this->setName(obj.name);
    return *this;
}

Identifier::~Identifier(){};

Identifier::Identifier(std::string nameParam) {
	name = nameParam;
}

std::string Identifier::getName() {
	return name;
}

void Identifier::setName(std::string nameParam) {
	name = nameParam;
}


void Identifier::write(QJsonObject &json) const {
    json["name"]= QString::fromStdString(name);
}

void Identifier::read(const QJsonObject &json){
    if (json.contains("name") && json["name"].isString())
           name = json["name"].toString().toUtf8().constData();
}


std::string Identifier::toString() {
    return "(Identifier = " + name+" )";
}

