#include <iostream>
#include "repositoryinterface.h"

RepositoryInterface::RepositoryInterface(){
    
}

QString RepositoryInterface::openFile(QString fileName){
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        return "error";
    }
    QTextStream in(&file);
    QString text = in.readAll();
    file.close();
    return text;
}

bool RepositoryInterface::saveFile(QString fileName, QString text){
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QFile::Text)){
        return false;
    }
    QTextStream out(&file);
    out << text;
    file.close();
    return true;
}

bool RepositoryInterface::getSource(std::string fileName, std::vector<std::string>& outVec){
    QFile file(QString::fromStdString(fileName));
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        return false;
    }
    QString text;
    QTextStream in(&file);
    while(!in.atEnd()){

        text = in.readLine();
        // Check to see if line is not empty, or if it is a comment
        if(text.size() > 0 && text.front()!='#'){
            outVec.push_back(text.toUtf8().constData());
        }
    }
    file.close();
    return true;
}


void RepositoryInterface::storeCompiled(QString fileName, QJsonObject* vec){
    //QString saveName = QDir::currentPath()+repoPath+fileName+"-Compiled.json";
    QFile saveFile(fileName+"-Compiled.json");
    if (!saveFile.open(QIODevice::WriteOnly)) {
            std::cout << "could not open file to save compilation" << std::endl;
    }
    QJsonDocument doc(*vec);
    saveFile.write(doc.toJson());
}


void RepositoryInterface::getCompiled(QString fileName, QJsonObject& program){
    QJsonDocument doc;
    std::cout << "FileName: " << fileName.toUtf8().constData() << std::endl;
    QFile jsonFile(fileName+"-Compiled.json");
    if (!jsonFile.open(QIODevice::ReadOnly)) {
        std::cout << "could not open compiled file" << std::endl;
        return;
    }

    QByteArray savedProgram = jsonFile.readAll();
    doc = QJsonDocument::fromJson(savedProgram);
    //doc.fromJson(savedProgram);
    program = doc.object();
}

