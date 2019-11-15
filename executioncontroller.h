#ifndef EXECUTIONCONTROLLER_H
#define EXECUTIONCONTROLLER_H
#include "repositoryinterface.h"
#include "Program.h"
#include <vector>
#include <iostream>

class ExecutionController{
    public:
        ExecutionController();
        bool Run(QString);

    private:
        RepositoryInterface repo;
        std::string currentFile;
};


#endif // EXECUTIONCONTROLLER_H
