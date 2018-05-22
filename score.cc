#include "score.h"
using namespace std;

Score::Score() :curScore{ 0 }, highScore{ 0 } {}

int Score::getHighScore() const { return highScore; }

int Score::getCurrentScore() const { return curScore; }

void Score::addCurrentScore(int num) { 
	curScore += num; 
	if (curScore > highScore) setHighScore(curScore);
}

void Score::setHighScore(int num) { highScore = num; }

void Score::setCurrentScore(int num) { curScore = num; 
	if (curScore > highScore) setHighScore(curScore);
}
