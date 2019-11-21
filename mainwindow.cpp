#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}


void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File ", QDir::currentPath()+repoPath);
    QString input;
    input = repo.openFile(fileName);
    if(input == "error"){
        QMessageBox::warning(this,"Warning", "error cannot open file");
        return;
    }
    else{
        currentFile = fileName;
        setWindowTitle(fileName);
        ui->textEdit->setText(input);
    }
}

void MainWindow::on_actionSave_triggered()
{
    if(currentFile == ""){
        on_actionSave_As_triggered();
    }
    else {
        if(!repo.saveFile(currentFile, ui->textEdit->toPlainText())){
                QMessageBox::warning(this,"Warning", "File not Saved ");
            }
        else{
                QMessageBox::information(this, "Save Successful", "File Saved!");
                setWindowTitle(currentFile);
        }
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save File as ", QDir::currentPath()+repoPath);
    if(!repo.saveFile(fileName, ui->textEdit->toPlainText())){
            QMessageBox::warning(this,"Warning", "Cannot Save File ");
    }
    else{
        QMessageBox::information(this, "Save Successful", "File Saved!");
        currentFile = fileName;
        setWindowTitle(fileName);
    }

}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionDocumentation_triggered()
{
    QMessageBox::information(this,tr("Help"), tr("www.github.com/link_to_project_repo/Doc.txt"));
}

void MainWindow::on_actionCompile_triggered()
{
    CompilerController compiler;
    try {
        if(compiler.Run(currentFile)){
            QString result = "Program: " + currentFile + "has compiled to "+ currentFile+"-Compiled.json";
            QMessageBox::information(this,tr("Compilation Successful"),result);
        }
    } catch (std::string error){
        QString result ;
        result = "Program: " + currentFile + " has error: " + QString::fromStdString(error);
        QMessageBox::information(this,tr("Compilation Terminated"),result);
    }


}

void MainWindow::on_actionRun_triggered()
{
    //TODO: run compiled program
    ExecutionController executor(ui,this);
    try { 
    	executor.Run(currentFile);
    } catch(std::string error){
		QString result = "Program: " + currentFile + "has runtime error: " + QString::fromStdString(error);
		QMessageBox::information(this, tr("Execution Terminated"), result);
    } 
}

