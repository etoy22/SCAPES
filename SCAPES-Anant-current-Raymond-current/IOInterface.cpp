#include "IOInterface.h"

IOInterface::IOInterface(Ui::MainWindow& uiPtr, QMainWindow* window) : ui(uiPtr), win(window) {
};

int IOInterface::getUserInput(QString message){
	int input = -1;
	while(!(input >= 0)){
		input = QInputDialog::getInt(win, "Variable Input", message);
	}
	return input;
}

void IOInterface::displayProgramOutput(QString out){
    QString consoleOut = ui.Console->toPlainText();
    consoleOut.append(out);
    consoleOut.append(" \n");
    ui.Console->setText(consoleOut);
}
