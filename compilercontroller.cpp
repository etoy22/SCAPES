#include "compilercontroller.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <vector>
CompilerController::CompilerController(){
}

bool CompilerController::Run(QString fileName){
    // get source
    std::vector<std::string> in;
    std::vector<std::string> out;
    repo.getSource(fileName.toUtf8().constData(), in);
    Program program(fileName.toUtf8().constData(), in);
    
    try {
        if(program.compile()){
            QJsonObject compiledProgram;
            program.write(compiledProgram);
            repo.storeCompiled(fileName, &compiledProgram);
            return true;
        }
    } catch(std::string err) {
        throw;
    }
    return false;
}

