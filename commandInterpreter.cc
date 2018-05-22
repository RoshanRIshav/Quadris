#include "commandInterpreter.h"
#include <sstream>
#include <iostream>
using namespace std;

commandType commandInterpreter::parseInput(string s) {
	bool foundmatch = false; 
	//indicates if any command name starts with substring s
	bool duplicate = false; 
	//indicates if more than one command names start with substring s
	int index = -1;
	//indicates the index of the matching command name in commandList
	int mult = 1;
	stringstream input(s);
	string str;

	if ((input >> mult)) {//the input is prefixed with a number
		if ((!(input >> str))||(mult<0))
		    str = "invalid";
			//input is invalid if s only contains a number or mult is negative
	} else { //the input does not start with a number
		str = s;
	}

	for (int i = 0; i < numOfCommands; ++i) { //loop through commandList
		if (commandList.at(i).find(str) == 0) {
			if (foundmatch == true) { //if another command starts with str
			    duplicate = true; 
			} else { 
				foundmatch = true;
				index = i;
			}
		}
	}
	
	if ((foundmatch == true) && (duplicate == false)) {
		return commandType(index);
	}else {return commandType::invalid;};
}

int commandInterpreter::getMultiplier(string s) {
	stringstream input(s);
	int mult; //if no multiplier is supplied then default 1 is used
	if (input >> mult) return mult;
	return 1;
}

void commandInterpreter::rename(string orig, string newname) {
	int i;
	stringstream ss(newname);
	if(ss >> i) return; 	//new command names are not allowed to start
					//with numbers

	for(int i=0;i<numOfCommands;++i) {
		if (commandList.at(i) == orig) {
			commandList.at(i) = newname;
			break;
		}
	}
}

