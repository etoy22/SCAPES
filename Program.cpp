#include <iostream>
#include <string>
#include <iterator>
#include <iomanip>
#include "DeclIntStmt.h"
#include "AddStmt.h"
#include "DeclArrStmt.h"
#include "JEqStmt.h"
#include "JLessStmt.h"
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
#include <QJsonObject>

Program::Program(std::string name, std::vector<std::string>& code){
    setName(name);
    input = code;
};

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
	std::string message ="";
    	std::string unavalible[12] = {"dci","dca","rdi","prt","mov","add","cmp", "jls", "jmr", "jeq", "jmp", "end"};
	if(input.size() == 0){
		message = "no code";
		throw message;
	}
	//Adds all decleration of varriables and labels to there sets
    	for(int j = 0; j < int(input.size());j++){
		if(input[j].find('#') != std::string::npos){}
		else if(input[j].find('$') != std::string::npos){
			message = "invalide character on line "+ std::to_string(j+1);
			throw message;	
		}
		else if(input[j].find_first_not_of(" \t") != std::string::npos){
			std::string s = input[j];
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
				message = "dci error on line ";
				message += std::to_string(j+1);
				throw message;
			}
			else if(result[0] == "rdi" && result.size() != 2){
				message = "rdi error on line ";
				message += std::to_string(j+1);
				throw message;
			}
			else if(result[0] == "prt" && result.size() != 2){
				message = "prt error on line ";
				message += std::to_string(j+1);
				throw message;
			}
			else if(result[0] == "cmp" && result.size() != 3){
				message = "cmp error on line ";
				message += std::to_string(j+1);
					throw message;
			}
			else if(j == int(input.size())-1 && result[0] != "end"){
				message = "the last statement isn't end";
				throw message;
			}
			else if(result[0] == "end" && result.size() != 1){
				message = "end error on line ";
				message += std::to_string(j+1);
				throw message;
			}
			else if (result[0] == "mov" && result.size() != 3){
				message = "mov error on line ";
				message += std::to_string(j+1);
				throw message;
			}
			else if (result[0] == "dca" && result.size() != 3){
				message = "dca error on line ";
				message += std::to_string(j+1);
				throw message;
			}
			else if (result[0] == "add" && result.size() != 3){
				message = "add error on line ";
				message += std::to_string(j+1);
				throw message;
			}
			//Downloading into sets
			if(result[0] == "dci"){
				if(var.size()==0){
					var.insert(result[1]);
				}	
				else if(var.count(result[1])){
					message = "multiple of the same varriable declaired line ";
					message += std::to_string(j+1);
					throw message;
				}
				else{
					var.insert(result[1]);
				}
			}
			else if(result[0] == "dca"){
				if(var.count(result[1])){
					message = "multiple of the same varriable declaired line ";
					message += std::to_string(j+1);
					throw message;
				}
				else{
					bool test = false;
					try{
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
			else if (result[0] == "rdi" || result[0] == "prt"){
				if(var.count(result[1])== 0){
					message = "undeclaired varraible called line ";
					message += std::to_string(j+1);
					throw message;
				}
			}
			else if(result[0] == "cmp"||result[0] == "add"||result[0] == "mov"){
					if(var.count(result[1])== 0){
					message = "undeclaired varraible 1 called line ";
					message += std::to_string(j+1);
					throw message;
				}
				if(var.count(result[2])== 0){					
					message = "undeclaired varraible 2 called line ";
					message += std::to_string(j+1);
					throw message;
				}
			}
			//Checks that all the following are counted as an error but has no 
			else if(result[0] == "jmr"|| result[0] == "jmp"||result[0] == "end"||result[0] == "jeq"||result[0] == "jls"){}
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
}

void Program::print(){
}

std::string Program::getFileName(){
	return fileName;
}

int Program::getComparisonFlag(){
	return comparisonFlag;
}
