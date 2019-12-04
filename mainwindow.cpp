#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScrollArea>
#include <QTextEdit>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("SCAPES");
    ui->Console->setReadOnly(true);
    QPalette p = ui->Console->palette();
    QColor colour(211,211,211);
    p.setColor(QPalette::Base, colour);
    ui->Console->setPalette(p);
    setWindowIcon(QIcon(":/Images/Icons/SCAPEGOAT.bmp"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    setWindowTitle("SCAPES");
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
        setWindowTitle(currentFile);
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

bool MainWindow::autoSave(){
    repo.saveFile(currentFile, ui->textEdit->toPlainText());
    setWindowTitle(currentFile);
    return true;
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
    if(currentFile == "")
        on_actionSave_As_triggered();
    else
        autoSave();

    CompilerController compiler;
    try {
        if(compiler.Run(currentFile)){
            QString result = "Program: " + currentFile + "has compiled to "+ currentFile+"-Compiled.json";
            QMessageBox::information(this,tr("Compilation Successful"),result);
        }
    } catch (std::string error){
        QString result ;
        result = "Compilation Terminated \nProgram: " + currentFile + " has error: " + QString::fromStdString(error);
        ui->Console->setText(result);
    }
}

bool MainWindow::autoCompile(){
    CompilerController compiler;
    try{
        if(compiler.Run(currentFile))
            return true;
    } catch (std::string error){
        throw;
    }
    return false;
}

void MainWindow::on_actionRun_triggered()
{
    //auto save and compile
    if(currentFile == "")
        on_actionSave_As_triggered();
    else
        autoSave();

    try {
        if(autoCompile())
            QMessageBox::information(this,tr("Compilation Successful"),tr("Compilation Done, now Executing..."));
    } catch (std::string error) {
        QString result ;
        result = "Compilation Terminated \nProgram: " + currentFile + " has error: " + QString::fromStdString(error) + "\n Execution Aborted";
        ui->Console->setText(result);
        return;
    }


    // execution starts
    ExecutionController executor(ui,this);
    try { 
    	executor.Run(currentFile);
    } catch(std::string error){
		QString result = "Execution Terminated \nProgram: " + currentFile + "has runtime error: " + QString::fromStdString(error);
		ui->Console->setText(result);
    } 
}

