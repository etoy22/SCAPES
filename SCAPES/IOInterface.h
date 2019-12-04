#ifndef IOINTERFACE_HEADER
#define IOINTERFACE_HEADER

#include <QMainWindow>
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QIntValidator>

class IOInterface{

private:
	Ui::MainWindow ui;
	QMainWindow* win;

protected:
public:
    IOInterface(Ui::MainWindow&, QMainWindow*);
	int getUserInput(QString);
	void displayProgramOutput(QString);
};

#endif
