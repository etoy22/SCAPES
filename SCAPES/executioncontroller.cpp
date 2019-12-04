#include "executioncontroller.h"

ExecutionController::ExecutionController(Ui::MainWindow*& uiPtr, QMainWindow* window) : ui(*uiPtr), win(window) {
}

bool ExecutionController::Run(QString fileName){
    // get compiled
    ui.Console->setText("");
    QJsonObject programJsonObj;
    repo.getCompiled(fileName,programJsonObj);
    Program program(programJsonObj);
    IOInterface io(ui,win);
    program.setIO(io);
    try {
        program.execute();
    } catch(std::string s) {
        throw;
    }
    return true;
	    
}
