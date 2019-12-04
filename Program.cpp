#include <iostream>
#include <string>
#include <iterator>
#include <iomanip>
#include <regex>
#include "DeclIntStmt.h"
#include "EndStmt.h"
#include "JumpStmt.h"
#include "CompStmt.h"
#include "ReadStmt.h"
#include "PrintStmt.h"
#include "JumpMoreStmt.h"
#include "Variable.h"
#include "Program.h"
#include "AddStmt.h"
#include "DeclArrStmt.h"
#include "JEqStmt.h"
#include "JLessStmt.h"
#include "MovStmt.h"
#include "Identifier.h"
#include <QJsonObject>

// TODO: remove later
#include <QDebug>

Program::Program(std::string name, std::vector<std::string>& code){
    setName(name);
    input = code;
};

Program::Program(QJsonObject& code) {
	read(code);
    comparisonFlag = 0;  // jump more by default
};

Program::Program(std::string name, QJsonObject& code) {
	setName(name);	
	read(code);
    comparisonFlag = 0; // jump more by befault
};

Program::~Program() {
	if (statements.size() > 0) {
		for (unsigned i = 0; i < statements.size(); i++) {
			if (statements.at(i) != nullptr) {
				delete statements.at(i);
			}
		}
	}
	if (pairs.size() > 0) {
		for (unsigned i = 0; i < pairs.size(); i++) {
			if (pairs.at(i).first != nullptr) {
				delete pairs.at(i).first;
			}
		}
	}
}

void Program::setName(std::string name){
	fileName = name;
}

bool Program::compile(){
    bool result;
    try {
        result = checkSyntax();
    } catch (std::string error) {
        std::string errMsg =  "ERROR: " + error;
        throw errMsg;
	result = false;
    }
    if (result){
        //scan source

        for (unsigned long i =0; i<input.size(); i++) {
		std::string in = input.at(i); //line 1-n
		std::string temp = "x";
		std::string line = "";
             	int l=in.length();
             	line+=in[0];
              	for(int j=1;j<l;j++){
                  if(line[line.length()-1]==' ' && in[j]==' ')
                      continue;
                  else
                      line+=in[j];
             }
            if(line.find(":") != std::string::npos){
                std::string labe = line.substr(0, line.find(':'));
                line = line.substr(line.find(':') + 2, line.length());
                Label leb;
                leb.setName(labe);
                QJsonObject lab;
                QJsonObject labs;
                leb.write(lab);
                labs["Identifier"] = lab;
                out.push_back(labs);
            }
            if(line.find("dci") != std::string::npos){
                DeclIntStmt dci;
                dci.setLabel(dci.getLabel());
                dci.compile(line);
                QJsonObject stmt;
                dci.write(stmt);
                out.push_back(stmt);
            }
            else if (line.find("end") != std::string::npos) {
                EndStmt end;
                end.compile(line);
                QJsonObject stmt;
                end.write(stmt);
                out.push_back(stmt);
            }
            else if (line.find("jmp") != std::string::npos) {
                JumpStmt jmp;
                jmp.compile(line);
                QJsonObject stmt;
                jmp.write(stmt);
                out.push_back(stmt);
            }
            else if (line.find("cmp") != std::string::npos) {
                CompStmt cmp;
                cmp.compile(line);
                QJsonObject stmt;
                cmp.write(stmt);
                out.push_back(stmt);
            }
            else if (line.find("rdi") != std::string::npos) {
                ReadStmt rdi;
                rdi.compile(line);
                QJsonObject stmt;
                rdi.write(stmt);
                out.push_back(stmt);
            }
            else if (line.find("prt") != std::string::npos) {
                PrintStmt prt;
                prt.compile(line);
                QJsonObject stmt;
                prt.write(stmt);
                out.push_back(stmt);
            }
            else if (line.find("jmr") != std::string::npos) {
                JumpMoreStmt jmr;
                jmr.compile(line);
                QJsonObject stmt;
                jmr.write(stmt);
                out.push_back(stmt);
            }
            else if (line.find("dca") != std::string::npos) {
		DeclArrStmt dca;
		dca.compile(line);
		QJsonObject stmt;
                dca.write(stmt);
                out.push_back(stmt);
	    }    
	    else if (line.find("mov") != std::string::npos) {
		MovStmt mov;
		mov.compile(line);
		QJsonObject stmt;
                mov.write(stmt);
                out.push_back(stmt);
	    }  
	    else if (line.find("jls") != std::string::npos) {
		JLessStmt jls;
		jls.compile(line);
		QJsonObject stmt;
                jls.write(stmt);
                out.push_back(stmt);
	    } 
	    else if (line.find("jeq") != std::string::npos) {
		JEqStmt jeq;
		jeq.compile(line);
		QJsonObject stmt;
                jeq.write(stmt);
                out.push_back(stmt);
	    } 
	    else if (line.find("add") != std::string::npos) {
		AddStmt add;
		add.compile(line);
		QJsonObject stmt;
                add.write(stmt);
                out.push_back(stmt);
	    } 
        }
        return true;
    }
    return false;
}

void Program::read(const QJsonObject &json){
	int i = 0; int labelCount = 0;
	QJsonArray array = json.value("Program").toArray();

	foreach(const QJsonValue & v, array) {
		QJsonObject obj = v.toObject();

		if (obj.contains("Label")) {
			QJsonValue name = (obj.value("Label")).toObject().value("name");
			std::string instr = name.toString().toUtf8().constData();

			// TODO: somehow improve this process?
			if (!instr.compare("dci")) {
				DeclIntStmt* dci = new DeclIntStmt();
				dci->read(obj);
				statements.push_back(dci);
			}
			else if (!instr.compare("dca")) {
				DeclArrStmt* dca = new DeclArrStmt();
				dca->read(obj);
				statements.push_back(dca);
			}
			else if (!instr.compare("rdi")) {
				ReadStmt* rdi = new ReadStmt();
				rdi->read(obj);
				statements.push_back(rdi);
			}
			else if (!instr.compare("prt")) {
				PrintStmt* prt = new PrintStmt();
				prt->read(obj);
				statements.push_back(prt);
			}
			else if (!instr.compare("jmp")){
				JumpStmt* jmp = new JumpStmt();
				jmp->read(obj);
				statements.push_back(jmp);
			}
			else if (!instr.compare("jmr")){
				JumpMoreStmt* jmr = new JumpMoreStmt();
				jmr->read(obj);
				statements.push_back(jmr);
			}
			else if (!instr.compare("jls")){
				JLessStmt* jls = new JLessStmt();
				jls->read(obj);
				statements.push_back(jls);
			}
			else if (!instr.compare("jeq")){
				JEqStmt* jeq = new JEqStmt();
				jeq->read(obj);
				statements.push_back(jeq);
			}
			else if (!instr.compare("cmp")){
				CompStmt* cmp = new CompStmt();
				cmp->read(obj);
				statements.push_back(cmp);
			}
			else if (!instr.compare("add")) {
				AddStmt* add = new AddStmt();
				add->read(obj);
				statements.push_back(add);
			}
			else if (!instr.compare("mov")) {
				MovStmt* mov = new MovStmt();
				mov->read(obj);
				statements.push_back(mov);
			}
			i++;
		}
		else {
			QJsonObject id = obj.value("Identifier").toObject();
			Label* label = new Label();
			label->read(id);

			pairs.push_back(std::make_pair(label, i));
			labelCount++;
		}

	}

	// just for debugging purposes
	std::cout << std::endl;
	std::cout << "Label objects: " << std::endl;
	for (unsigned int k = 0; k < pairs.size(); k++) {
		std::cout << pairs.at(k).first->toString() << " | index (from 0) :" << pairs.at(k).second << std::endl;
	}
	// just for debugging purposes
	std::cout << std::endl;
	std::cout << "Instruction objects: " << std::endl;
	for (unsigned int l = 0; l < statements.size(); l++) {
		std::cout << statements.at(l)->toString() << std::endl;
	}
}

void Program::write(QJsonObject &json) const{
    json["Program"] = out;
}

bool Program::checkSyntax(){
	std::set <std::string> var;
	std::set <std::string> dvar;
	std::set <std::string> label;
	std::string message ="";
    	std::string unavalible[12] = {"dci","dca","rdi","prt","mov","add","cmp", "jls", "jmr", "jeq", "jmp", "end"};
	if(input.size() == 0){
		message = "no code";
		throw message;
	}
	
	//Adds all decleration of varriables and labels to there sets
    	for(int j = 0; j < int(input.size());j++){
		if(input[j].find('#') != std::string::npos){}
		else if(input[j].find_first_not_of(" \t") != std::string::npos){
			std::string s = input[j];
			std::istringstream iss(s);
			std::vector<std::string> result{
			    std::istream_iterator<std::string>(iss), {}
			};
			
			//Checks for labels
			if(result.size()>1){
				if(int(result[1].find(':'))!= -1){
					result[0] += ":";
					result.erase(result.begin()+1);
				}
			}
			if(int(result[0].find(':'))!= -1){
				bool test = false;
				try{
					if(stoi(result[0].substr(0,result[0].find(':')))==0){}
				}
				catch(std::invalid_argument& e)
				{
					test = true;
				}
				catch(std::out_of_range& e)
				{
					test = true;
				}
				if(!test){
					message = "literal used as label on line ";
					message += std::to_string(j+1);
					throw message;
				}
				label.insert(result[0].substr(0,result[0].find(':')));
				result.erase(result.begin());
			}
		
			//error checking that it ends
			
			if(j == int(input.size())-1 && result[0] != "end"){
				message = "the last statement isn't end";
				throw message;
			}
			
			//checking stmt
			if(result[0] == "dci"){	
				if(result.size() != 2){
					message = "dci error on line ";
					message += std::to_string(j+1);
					throw message;
				}
				if(var.count(result[1])||dvar.count(result[1])){
					message = "multiple of the same varriable declaired line ";
					message += std::to_string(j+1);
					throw message;
				}
				else if(result[1].find('$') != std::string::npos){
					message = "used an invalid char on line "+ std::to_string(j+1);
					throw message;	
				}
				else{
					bool test = false;
					try{
						int t = stoi(result[1]);
						t++;
					}
					catch(std::invalid_argument& e)
					{
						test = true;
					}
						catch(std::out_of_range& e)
					{
						test = true;
					}
					if(!test){
						message = "literal used as varriables on line ";
						message += std::to_string(j+1);
					   	throw message;
					}
					var.insert(result[1]);
				}
			}
			else if(result[0] == "dca"){
				if (result.size() != 3){
					message = "dca error on line ";
					message += std::to_string(j+1);
					throw message;
				}
				if(var.count(result[1])||dvar.count(result[1])){
					message = "multiple of the same varriable declaired line ";
					message += std::to_string(j+1);
					throw message;
				}
				else{
					bool test = false;
					bool test2 = false;
					try{
						int t = stoi(result[1]);
						t++;
					}
					catch(std::invalid_argument& e)
					{
						test2 = true;
					}
						catch(std::out_of_range& e)
					{
						test2 = true;
					}
					if(!test2){
						message = "literal used as varriables on line ";
						message += std::to_string(j+1);
					   	throw message;
					}
					try{
						dvar.insert(result[1]);
						for(int i = 0; i< stoi(result[2]);i++){
							std::string temp = "$"+result[1]+"+"+std::to_string(i);
							var.insert(temp);
						}
					}
					catch(std::invalid_argument& e)
					{
						test = true;
					}
					catch(std::out_of_range& e)
					{
						test = true;
					}
					if(test){
						message = "error with dca ";
						message += std::to_string(j+1);
						throw message;
					}
				}
			}
			else if (result[0] == "rdi"){ 
				if(result.size() != 2){
					message = "rdi error on line ";
					message += std::to_string(j+1);
					throw message;
				}
				if(result[1][0] == '$'){
					std::string sub = result[1].substr(1, result[1].find_last_of("+")-1);
					if(dvar.count(sub)==0){
						message = "undeclaired varraible called line ";
						message += std::to_string(j+1);
						throw message;	
					}
					sub = result[1].substr(result[1].find_last_of("+")+1, result[1].size()-1);
					bool ending = false;
					try{
						if(stoi(sub)==0){}
					}
					catch(std::invalid_argument& e)
					{
						ending = true;
					}
					catch(std::out_of_range& e)
					{
						ending = true;
					}
					if(ending){
						if(var.count(sub)== 0){
							message = "undeclaired varraible called on line ";
							message += std::to_string(j+1);
							throw message;
						}
					}
				}
				else{
					bool test = false;
					try{
						if(stoi(result[1])==0){}
					}
					catch(std::invalid_argument& e)
					{
						test = true;
					}
					catch(std::out_of_range& e)
					{
						test = true;
					}
					if(!test){
						message = "literal called on line ";
						message += std::to_string(j+1);
						throw message;
					}
					if(var.count(result[1])== 0){
						message = "undeclaired varraible called line ";
						message += std::to_string(j+1);
						throw message;
					}
				}
			}
			else if (result[0] == "prt"){
 				if(result.size() == 1){
					message = "invalid call for prt line ";
					message += std::to_string(j+1);
					throw message;
				}
				
				std::string temp = "";
				for(unsigned int x = 1; x < result.size(); x++){
					temp = temp + " " + result[x];
				}
				if(temp[1] == '\"' && temp[temp.size()-1]=='\"'){}
				else if(result.size() == 2){
					if(result[1][0] == '$'){
						std::string sub = result[1].substr(1, result[1].find_last_of("+")-1);
						if(dvar.count(sub)==0){
							message = "undeclaired varraible called line ";
							message += std::to_string(j+1);
							throw message;	
						}
						sub = result[1].substr(result[1].find_last_of("+")+1, result[1].size()-1);
						bool ending = false;
						try{
							if(stoi(sub)==0){}
						}
						catch(std::invalid_argument& e)
						{
							ending = true;
						}
						catch(std::out_of_range& e)
						{
							ending = true;
						}
						if(ending){
							if(var.count(sub)== 0){
								message = "undeclaired varraible called on line ";
								message += std::to_string(j+1);
								throw message;
							}
						}
					}
					else{
						bool test = false;
						try{
							if(stoi(result[1])==0){}
						}
						catch(std::invalid_argument& e)
						{
							test = true;
						}
						catch(std::out_of_range& e)
						{
							test = true;
						}
						if(var.count(result[1])== 0 && test){
							message = "undeclaired varraible called line ";
							message += std::to_string(j+1);
							throw message;
						}
					}
				}
				else{
					message = "invalid call for prt line ";
					message += std::to_string(j+1);
					throw message;
				}
			}
			else if(result[0] == "add"||result[0] == "mov"){
				if (result.size() != 3){
					message = result[0] +" error on line ";
					message += std::to_string(j+1);
					throw message;
				}
				if(result[1][0] == '$'){
					std::string sub = result[1].substr(1, result[1].find_last_of("+")-1);
					if(dvar.count(sub)==0){
						message = "undeclaired varraible called line ";
						message += std::to_string(j+1);
						throw message;	
					}
					sub = result[1].substr(result[1].find_last_of("+")+1, result[1].size()-1);
					bool ending = false;
					try{
						if(stoi(sub)==0){}
					}
					catch(std::invalid_argument& e)
					{
						ending = true;
					}
					catch(std::out_of_range& e)
					{
						ending = true;
					}
					if(ending){
						if(var.count(sub)== 0){
							message = "undeclaired varraible called on line ";
							message += std::to_string(j+1);
							throw message;
						}
					}
				}
				else
				{
					bool test = false;
					try{
						if(stoi(result[1])==0){}
					}
					catch(std::invalid_argument& e)
					{
						test = true;
					}
					catch(std::out_of_range& e)
					{
						test = true;
					}
					if(var.count(result[1])== 0 &&test){
						message = "undeclaired varraible 1 called line ";
						message += std::to_string(j+1);
						throw message;
					}
				}
				if(result[2][0] == '$'){
					std::string sub = result[2].substr(1, result[2].find_last_of("+")-1);
					if(dvar.count(sub)==0){
						message = "undeclaired varraible called line ";
						message += std::to_string(j+1);
						throw message;	
					}
					sub = result[2].substr(result[2].find_last_of("+")+1, result[2].size()-1);
					bool ending = false;
					try{
						if(stoi(sub)==0){}
					}
					catch(std::invalid_argument& e)
					{
						ending = true;
					}
					catch(std::out_of_range& e)
					{
						ending = true;
					}
					if(ending){
						if(var.count(sub)== 0){
							message = "undeclaired varraible called on line ";
							message += std::to_string(j+1);
							throw message;
						}
					}
				}
				else {
				
					if(var.count(result[2])== 0){					
						message = "undeclaired varraible 2 called line ";
						message += std::to_string(j+1);
						throw message;
					}
				}
			}
			else if(result[0] == "cmp"){
				if(result.size() != 3){
					message = "cmp error on line ";
					message += std::to_string(j+1);
					throw message;
				}
				if(result[1][0] == '$'){
					std::string sub = result[1].substr(1, result[1].find_last_of("+")-1);
					if(dvar.count(sub)==0){
						message = "undeclaired varraible called line ";
						message += std::to_string(j+1);
						throw message;	
					}
					sub = result[1].substr(result[1].find_last_of("+")+1, result[1].size()-1);
					bool ending = false;
					try{
						if(stoi(sub)==0){}
					}
					catch(std::invalid_argument& e)
					{
						ending = true;
					}
					catch(std::out_of_range& e)
					{
						ending = true;
					}
					if(ending){
						if(var.count(sub)== 0){
							message = "undeclaired varraible called on line ";
							message += std::to_string(j+1);
							throw message;
						}
					}
				}
				else{
					bool test = false;
					try{
						if(stoi(result[1])==0){}
					}
					catch(std::invalid_argument& e)
					{
						test = true;
					}
					catch(std::out_of_range& e)
					{
						test = true;
					}
					if(var.count(result[1])== 0&&test){
						message = "undeclaired varraible 1 called line ";
						message += std::to_string(j+1);
						throw message;
					}
				}
				if(result[2][0] == '$'){
					std::string sub = result[2].substr(1, result[2].find_last_of("+")-1);
					if(dvar.count(sub)==0){
						message = "undeclaired varraible called line ";
						message += std::to_string(j+1);
						throw message;	
					}
					sub = result[2].substr(result[2].find_last_of("+")+1, result[2].size()-1);
					bool ending = false;
					try{
						if(stoi(sub)==0){}
					}
					catch(std::invalid_argument& e)
					{
						ending = true;
					}
					catch(std::out_of_range& e)
					{
						ending = true;
					}
					if(ending){
						if(var.count(sub)== 0){
							message = "undeclaired varraible called on line ";
							message += std::to_string(j+1);
							throw message;
						}
					}
				}
				else{
					bool test2 = false;
					try{
						if(stoi(result[2])==0){}
					}
					catch(std::invalid_argument& e)
					{
						test2 = true;
					}
					catch(std::out_of_range& e)
					{
						test2 = true;
					}
					
					if(var.count(result[2])== 0&&test2){					
						message = "undeclaired varraible 2 called line ";
						message += std::to_string(j+1);
						throw message;
					}
				}
			}
			else if(result[0] == "end"){
				if( result.size() != 1){
					message = "end error on line ";
					message += std::to_string(j+1);
					throw message;
				}
			}
			//Checks that all the following are counted as an error but has no 
			else if(result[0] == "jmr"|| result[0] == "jmp"||result[0] == "jeq"||result[0] == "jls"){}
			else{
				message = "invalid call on line ";
				message += std::to_string(j+1);
				throw message;	
			}
		}
			
	}
	//second loop to see all labels
    	for(int j = 0; j < int(input.size());j++){
		if(input[j].find_first_not_of(" \t") != std::string::npos){
			std::string s = input[j];
			std::istringstream iss(s);
			std::vector<std::string> result{
			    std::istream_iterator<std::string>(iss), {}
			};
			if(result[0] == "jmr"|| result[0] == "jmp"||result[0] == "jeq"||result[0] == "jls"){
				if(label.count(result[1]) ==0){
					message = "undeclaired label on line ";
					message += std::to_string(j+1);
					throw message;
				}
			}
		}
	}
	//Loops to check if a statement is used as a label
	for(int i = 0; i < 12;i++){
		
		if(label.count(unavalible[i])){
		    message = "used a statement as a label ";
		   throw message;
		} 
	}
	
	//Iterates through label to check if label and end are the same
	std::set<std::string>::iterator it = label.begin();
	while (it != label.end())
	{
		if(var.count(*it)){
		    	message = "a varriable and a label have the same name";
		   	throw message;
		}
		it++;
	}
	return true;	
}

void Program::execute(){

    try{
        for (unsigned int i = 0; i < statements.size(); i++) {
            if (typeid(*(statements.at(i))) == typeid(DeclIntStmt))
                statements.at(i)->run(variables,ui,NULL, NULL);

            else if (typeid(*(statements.at(i))) == typeid(DeclArrStmt))
                statements.at(i)->run(variables,ui,NULL, NULL);

            else if (typeid(*(statements.at(i))) == typeid(ReadStmt))
                statements.at(i)->run(variables, ui, win, NULL);

            else if (typeid(*(statements.at(i))) == typeid(PrintStmt))
                statements.at(i)->run(variables, ui, win, NULL);

            else if (typeid(*(statements.at(i))) == typeid(JumpStmt))
                i = statements.at(i)->run(variables, ui, win, &pairs);

            else if (typeid(*(statements.at(i))) == typeid(JumpMoreStmt)){
                if(comparisonFlag == 2)
                    i = statements.at(i)->run(variables, ui, win, &pairs);
            }
            else if (typeid(*(statements.at(i))) == typeid(JEqStmt)){
                if(comparisonFlag == 0)
                    i = statements.at(i)->run(variables, ui, win, &pairs);
            }
            else if (typeid(*(statements.at(i))) == typeid(JLessStmt)){
                if(comparisonFlag == 1)
                    i = statements.at(i)->run(variables, ui, win, &pairs);
            }
            else if (typeid (*(statements.at(i))) == typeid(CompStmt))
                comparisonFlag = statements.at(i)->run(variables, ui, NULL, NULL);
			else if (typeid(*(statements.at(i))) == typeid(AddStmt)) {
				statements.at(i)->run(variables, ui, NULL, NULL);
			}
			else if (typeid(*(statements.at(i))) == typeid(MovStmt)) {
				statements.at(i)->run(variables, ui, NULL, NULL);
			}
		}
    }
    catch (std::string exeError){
            throw exeError;
    }

	// debugging: remove later
	std::cout << std::endl;
	std::cout << "Variable objects: " << std::endl;
	for (Variable* v : variables) {
		std::cout << "Variable: " + v->getName() + "   Value: " + std::to_string(v->getValue()) << std::endl;
	}

	
}

void Program::print(){
}

void Program::setUIPointer(Ui::MainWindow& ptr){
	ui = &ptr;
}

void Program::setWindowPointer(QMainWindow* window){
	win = window;
}

std::string Program::getFileName(){
	return fileName;
}

int Program::getComparisonFlag(){
	return comparisonFlag;
}
