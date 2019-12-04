#ifndef EXECUTIONCONTROLLER_H
#define EXECUTIONCONTROLLER_H
#include "repositoryinterface.h"
#include "Program.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <vector>
#include <iostream>
#include "IOInterface.h"

class ExecutionController{
    public:
	ExecutionController(Ui::MainWindow*&, QMainWindow*);
        bool Run(QString);

    private:
        RepositoryInterface repo;
        std::string currentFile;
		Ui::MainWindow ui;
		QMainWindow* win;
};


#endif // EXECUTIONCONTROLLER_H
