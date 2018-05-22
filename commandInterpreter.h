#ifndef COMMANDINTERPRETER_H
#define COMMANDINTERPRETER_H
#include <string>
#include <vector>

enum class commandType {
	left = 0, right, down, clockwise, counterclockwise, \
	drop, levelup, leveldown, norandom, random, sequence, \
	restart, hint,  I, J, L, O, S, Z, T, invalid
};

class commandInterpreter{
	std::vector<std::string> commandList = 
	{
	"left", "right", "down", "clockwise", "counterclockwise",
	"drop", "levelup", "leveldown", "norandom", "random",
	"sequence", "restart", "hint", "I", "J", "L", "O", "S",
	"Z", "T" , "invalid"
	};
	int numOfCommands;
public:
	commandInterpreter(){
		numOfCommands = commandList.size();
	}
	commandType parseInput(std::string s);
	int getMultiplier(std::string s);
	void rename(std::string orig, std::string newname);
};


#endif
