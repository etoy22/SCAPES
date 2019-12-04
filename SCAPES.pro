#-------------------------------------------------
#
# Project created by QtCreator 2019-11-02T21:35:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SCAPES
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        compilercontroller.cpp \
        executioncontroller.cpp \
        main.cpp \
        mainwindow.cpp \
        repositoryinterface.cpp \
	AddStmt.cpp \
	CompStmt.cpp \
	DeclArrStmt.cpp \
	DeclIntStmt.cpp \
	EndStmt.cpp \
	JEqStmt.cpp \
	JLessStmt.cpp \
	JumpStmt.cpp \
	Identifier.cpp \
	Label.cpp \
	MovStmt.cpp \
	Operand.cpp \
	Statement.cpp \
	Variable.cpp \
	JumpMoreStmt.cpp \
	ReadStmt.cpp \
	PrintStmt.cpp \
	Program.cpp \
	IOInterface.cpp \
	

HEADERS += \
        compilercontroller.h \
        executioncontroller.h \
        mainwindow.h \
        repositoryinterface.h \
	AddStmt.h \
	CompStmt.h \
	DeclArrStmt.h \
	DeclIntStmt.h \
	EndStmt.h \
	JEqStmt.h \
	JLessStmt.h \
	JumpStmt.h \
	Identifier.h \
	Label.h \
	MovStmt.h \
	Operand.h \
	Statement.h \
	Variable.h \
	JumpMoreStmt.h \
	ReadStmt.h \
	PrintStmt.h \
	Program.h \
        IOInterface.h \

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin

RESOURCES += \
    resources.qrc
