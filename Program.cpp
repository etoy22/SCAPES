#include <iostream>
#include <string>
#include <iterator>
#include <iomanip>
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
    source = code;
};

// TODO: removed compile = code for now
Program::Program(std::string name, QJsonObject& code){
    setName(name);
	code = code;
};

Program::Program(QJsonObject& code) {
	int i = 0;
	QJsonArray array = code.value("Program").toArray();

	foreach(const QJsonValue & v, array) {
		QJsonObject obj = v.toObject();		
		
		if (obj.contains("Label")) {
			QJsonValue name = (obj.value("Label")).toObject().value("name");
			std::string instr = name.toString().toUtf8().constData();
			std::cout << "Value = " << instr << std::endl;

			// TODO: somehow improve this process?
			if (!instr.compare("dci")) {
				DeclIntStmt* dci = new DeclIntStmt();
				dci->read(obj);
				statements.push_back(dci);
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

		}
		else {
			QJsonObject id = obj.value("Identifier").toObject();
			Label* label = new Label();
			label->read(id);

			pairs.push_back(std::make_pair(label, i));
		}
		i++;
	}

	// just for debugging purposes
	std::cout << std::endl;
	for (unsigned int k = 0; k < pairs.size(); k++) {
		std::cout << pairs.at(k).first->toString() << " | index (from 0) :" << pairs.at(k).second << std::endl;
	}
	// just for debugging purposes
	std::cout << std::endl;
	for (unsigned int l = 0; l < statements.size(); l++) {
		std::cout << statements.at(l)->toString() << std::endl;
	}

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
    }
    if (result){
        //scan source
        
        for (unsigned long i =0; i<source.size(); i++) {
        std::string in = source.at(i); //line 1-n
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
        }
        return true;
    }
    return false;
}

void Program::read(const QJsonObject &json){
    if(json.contains("Program") && json["Program"].isArray()){
        out = json["Program"].toArray();
    }
    
}

void Program::write(QJsonObject &json) const{
    json["Program"] = out;
}

bool Program::checkSyntax(){
	std::set <std::string> var;
	std::set <std::string> label;
	bool valid = true;
	std::string message ="";
    	std::string unavalible[12] = {"dci","dca","rdi","prt","mov","add","cmp", "jls", "jmr", "jeq", "jmp", "end"};
    if(source.size() == 0){
		valid = false;
	}
	//Adds all decleration of varriables and labels to there sets
    for(int j = 0; j < int(source.size()) &&valid;j++){
        if(source[j].find('#') != std::string::npos){}
        else if(source[j].find_first_not_of(" \t") != std::string::npos){
            std::string s = source[j];
			std::istringstream iss(s);
			std::vector<std::string> result{
			    std::istream_iterator<std::string>(iss), {}
			};
			if(result.size()>1){
			if(int(result[1].find(':'))!= -1){
				result[0] += ":";
				result.erase(result.begin()+1);
				}
			}
            		if (int(result[0].find(':')) != -1){
		        	if(label.size() == 0){
				    label.insert(result[0].substr(0,result[0].find(':')));
				    result.erase(result.begin());
				}
				else if(label.find(result[0].substr(0,result[0].find(':')))!= label.end()){
				    valid = false;
				    message = "two labels with the same name on line ";
				    message += std::to_string(j+1);
				    throw message;
				}
				else{
				    label.insert(result[0].substr(0,result[0].find(':')));
				    result.erase(result.begin());
				}
			}
			
			
			//error checking
			if(result[0] == "dci" && result.size() != 2){
				valid = false;
				message = "dci error on line ";
				message += std::to_string(j+1);
				throw message;
			}
			else if(result[0] == "rdi" && result.size() != 2){
				valid = false;
				message = "rdi error on line ";
				message += std::to_string(j+1);
				throw message;
			}
			else if(result[0] == "prt" && result.size() != 2){
				valid = false;
				message = "prt error on line ";
				message += std::to_string(j+1);
				throw message;
			}
			else if(result[0] == "cmp" && result.size() != 3){
				valid = false;
				message = "cmp error on line ";
				message += std::to_string(j+1);
					throw message;
			}

			else if(j == int(input.size())-1 && result[0] != "end"){

				valid = false;
				message = "the last statement isn't end";
				throw message;
			}
			else if(result[0] == "end" && result.size() != 1){
				valid = false;
				message = "end error on line ";
				message += std::to_string(j+1);
				throw message;
			}
			//Checking there are no errors
			if(valid){
				//Downloading into sets
				if(result[0] == "dci"){
					if(var.size()==0){
						var.insert(result[1]);
						}	
					else if(var.count(result[1])){
						valid = false;
						message = "multiple of the same varriable declaired line ";
						message += std::to_string(j+1);
						throw message;
					}
					else{
						var.insert(result[1]);
					}
				}
				else if (result[0] == "rdi" || result[0] == "prt"){
					if(var.count(result[1])== 0){
						valid = false;
						message = "undeclaired varraible called line ";
						message += std::to_string(j+1);
						throw message;
					}
				}
				else if(result[0] == "cmp"){
					if(var.count(result[1])== 0){
						valid = false;
						message = "undeclaired varraible 1 called line ";
						message += std::to_string(j+1);
						throw message;
					}
					if(var.count(result[2])== 0){
						valid = false;
						message = "undeclaired varraible 2 called line ";
						message += std::to_string(j+1);
						throw message;
					}
				}

				//Checks that all the following are counted as an error but has no 

				else if(result[0] == "jmr" || result[0] == "jmp"||result[0] == "end"){}

				else{
					valid = false;
					message = "invalid call on line ";
					message += std::to_string(j+1);
					throw message;
					
				}
						
			}
		}
			
	}
	//second loop to see all labels
        for(int j = 0; j < int(source.size()) &&valid;j++){
        if(source[j].find_first_not_of(" \t") != std::string::npos){
            std::string s = source[j];
			std::istringstream iss(s);
			std::vector<std::string> result{
			    std::istream_iterator<std::string>(iss), {}
			};
			if(result[0] == "jmr" || result[0] == "jmp"){
				if(label.count(result[1]) ==0){
					valid = false;
					message = "undeclaired label on line ";
					message += std::to_string(j+1);
					throw message;
				}
			}
		}
	}
	for(int i = 0; i < 12;i++){
		if(label.count(unavalible[i])){
		    valid = false;
		    message = "used a statement as a label ";
		   throw message;
		} 
	}
	std::set<std::string>::iterator it = label.begin();


	while (it != label.end())
	{
		if(var.count(*it)){
			valid = false;
		    message = "a varriable and  a label have the same name";
		   	throw message;
		}
		it++;
	}
	
    return valid;
}

void Program::execute(){
}

void Program::print(){
}

std::string Program::getFileName(){
	return fileName;
}

int Program::getComparisonFlag(){
	return comparisonFlag;
}
