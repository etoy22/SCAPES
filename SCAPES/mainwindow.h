#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <iostream>
#include <QMainWindow>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include "repositoryinterface.h"
#include "compilercontroller.h"
#include "executioncontroller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionExit_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionDocumentation_triggered();

    void on_actionCompile_triggered();

    void on_actionRun_triggered();

    void on_actionSave_As_triggered();

    bool autoSave();

    bool autoCompile();

private:
    Ui::MainWindow *ui;
    QString currentFile = "";
    RepositoryInterface repo;
    QString repoPath = "/Repository";
};

#endif // MAINWINDOW_H
