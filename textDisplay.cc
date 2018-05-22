#include <vector>
#include <utility>
#include <iostream>
#include <string>
#include "textDisplay.h"
#include "score.h"
#include "level.h"
#include "cell.h"
#include "board.h"
using namespace std;
TextDisplay::TextDisplay(int rows, int cols): rows{rows}, cols{cols}{
	//Initiallizing the gameBoard display
	for(int i = 0; i < rows; i++){
		vector<char> col;
		for(int j = 0; j < cols; j++){
			char emp = ' ';
			col.emplace_back(emp);
		}
		theDisplay.emplace_back(col);
	}
	//Initiallizing the preview display
	for(int i = 0; i < 2; i++){
		vector<char> col;
		for(int j = 0; j < 4; j++){
			char emp = ' ';
			col.emplace_back(emp);
		}
		previewDisplay.emplace_back(col);
	}
}


void TextDisplay::notify(Cell &whoNotified){
	Color whichColor = whoNotified.getColor();
	Coordinate coord = whoNotified.getCoord();
	if(whichColor == Color::I){
		theDisplay[(rows - 1) - coord.y][coord.x] = 'I';
	}
	else if(whichColor == Color::J){
		theDisplay[(rows - 1) - coord.y][coord.x] = 'J';
	}
	else if(whichColor == Color::L){
		theDisplay[(rows - 1) - coord.y][coord.x] = 'L';
	}
	else if(whichColor == Color::O){
		theDisplay[(rows - 1) - coord.y][coord.x] = 'O';
	}
	else if(whichColor == Color::S){
		theDisplay[(rows - 1) - coord.y][coord.x] = 'S';
	}
	else if(whichColor == Color::Z){
		theDisplay[(rows - 1) - coord.y][coord.x] = 'Z';
	}
	else if(whichColor == Color::T){
		theDisplay[(rows - 1) - coord.y][coord.x] = 'T';
	}
	else if(whichColor == Color::C){
		theDisplay[(rows - 1) - coord.y][coord.x] = '*';
	}
	else if(whichColor == Color::H){
		theDisplay[(rows - 1) - coord.y][coord.x] = '?';
	}
	else if(whichColor == Color::Empty){
		theDisplay[(rows - 1) - coord.y][coord.x] = ' ';
	}
	else{
		theDisplay[(rows - 1) - coord.y][coord.x] = 'X';
	}
}

//Modify the previewBoard based on the next block's color
void TextDisplay::modifyPreviewBoard(Color NewBlock){
	int index;
	char toDisplay;
	if(NewBlock == Color::I) {
		index = 0;
		toDisplay = 'I';
	}
	else if (NewBlock == Color::J) {
		index = 1;
		toDisplay = 'J';
	}
	else if(NewBlock == Color::L) {
		index = 2;
		toDisplay = 'L';
	}
	else if(NewBlock == Color::O){
		index = 3;
		toDisplay = 'O';
	}
	else if (NewBlock == Color::S){
		index = 4;
		toDisplay = 'S';
	}
	else if (NewBlock == Color::Z) {
		index = 5;
		toDisplay = 'Z';
	}
	else if (NewBlock == Color::T) {
		index = 6;
		toDisplay = 'T';
	}
	for(int i = 0; i < 4; i++){
		previewDisplay[previewBlocks[index][i].x][previewBlocks[index][i].y] = toDisplay;
	}
}
void TextDisplay::notify(Board &whoNotified){

	boardState currState = whoNotified.getState();
	Color nextBlock = currState.getColor();
	Score currScore = currState.getScore();
	score = currScore.getCurrentScore();
	hiScore = currScore.getHighScore();
	level = currState.getLevel();
	isFull = currState.isOver();
	playerName = currState.getPlayerName();
	//Refresh nextBlockPreview
	for(int i = 0; i < rowsPreview; i++){
		for(int j = 0; j < colsPreview; j++){
			previewDisplay[i][j] = ' ';
		}
	}
	modifyPreviewBoard(nextBlock);
}
//TODO:
/*
	1. Add some messages for highScore achievement
	2. Make sure everything is working properly
*/
ostream &operator<<(ostream &out, const TextDisplay &td) {
	if(td.isFull){
		out << "Game Over" << endl;
		return out;
	}
	//Add score, curr score and high score
	out << "Level:	  " << td.level << endl;
	out << "Score:	  " << td.score << endl;
	out << "Hi Score: " << td.hiScore << endl;
	if(td.playerName != "noNameSupplied"){
		out << "Player:   " << td.playerName << endl;
	}
	//The start of the actual game area
	//marked by a line of "_"
	for(int i = 0; i < td.cols; i++){
		out << "_";
	}
	out << endl;
	for(int i = 0; i < td.rows; i++){
		for(int j = 0; j <td.cols; j++){
			// out <<
			out << td.theDisplay[i][j];
		}
		// cout << i;
	out << endl;
	}
	//The end of the actual game area
	//marked by a line of "_"
	for(int i = 0; i < td.cols; i++){
		out << "_";
	}
	out << endl;
	//Print the next block;
	out << "Next:" << endl;
	for(int i = 0; i < td.rowsPreview; i++){
		for(int j = 0; j < td.colsPreview; j++){
			out << td.previewDisplay[i][j];
		}
		out<<endl;
	}
	out << endl;
	return out;
}
