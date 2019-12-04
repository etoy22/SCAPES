#ifndef REPOSITORYINTERFACE_H
#define REPOSITORYINTERFACE_H

#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QTextStream>
#include <fstream>
#include <vector>
//#include "Program.h"
#include <QJsonObject>
#include <QJsonDocument>

class RepositoryInterface{

    public:
        RepositoryInterface();
        bool saveFile(QString,QString);
        QString openFile(QString);
        bool getSource(std::string, std::vector<std::string>&);
        void storeCompiled(QString,QJsonObject*);
        void getCompiled(QString, QJsonObject&);
        

    private:
        QDir dir;
        QFileDialog dialog;
        QString repoPath = "/Repository";
        
};




#endif // RepositoryInterface
