#ifndef COMPILERCONTROLLER_H
#define COMPILERCONTROLLER_H
#include "repositoryinterface.h"
#include "Program.h"
#include <vector>
#include <iostream>

class CompilerController{
    public:
        CompilerController();
        bool Run(QString);

    private:
        RepositoryInterface repo;
        std::string currentFile;
};


#endif // COMPILERCONTROLLER_H
