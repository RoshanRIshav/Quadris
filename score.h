#ifndef SCORE_H
#define SCORE_H

class Score {
	int curScore;
	int highScore;
public:
	Score();
	int getHighScore() const;
	int getCurrentScore() const;
	void addCurrentScore(int num);
	void setHighScore(int num);
	void setCurrentScore(int num);
};

#endif
