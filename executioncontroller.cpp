#include "executioncontroller.h"

ExecutionController::ExecutionController(){
}

bool ExecutionController::Run(QString fileName){
    // get compiled
    QJsonObject programJsonObj;
    repo.getCompiled(fileName,programJsonObj);
    Program program(programJsonObj);
    try {
        program.execute();
    } catch(std::string s) {
	throw;
    }
	    
}
