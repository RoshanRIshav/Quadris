#ifndef BOARD_H
#define BOARD_H
#include <memory>
#include <vector>
#include <iostream>
#include "color.h"
#include "cell.h"
#include "score.h"
#include "level.h"
#include "subject.h"
#include "block.h"

class TextDisplay;

const int buffer = 3; //indicates how many rows are provided as buffer zones
class boardState {
    Score score;
    Color color;
    int level;
    bool over;
    //extra feature
    std::string playerName;
    public:
    boardState(Score s, Color c, int level, bool o, std::string name);
    Score getScore();
    Color getColor();
    int getLevel();
    bool isOver();
    //extra feature
    std::string getPlayerName();
};

class Board : public Subject {
    std::vector<std::vector<std::shared_ptr<Cell>>> theBoard;
    std::vector<std::shared_ptr<Block>> droppedBlock;
    size_t r;
    size_t c;
    std::shared_ptr<TextDisplay> td;
    Score score;
    int level;
    bool over = false;
    bool ifgraphic = true;
    std::shared_ptr<Block> nextBlock;
    //extra feature:
    std::string playerName = "noNameSupplied";
    
public:
    Board(size_t r, size_t c, std::shared_ptr<TextDisplay> td, int level);
    ~Board();
    void setOver(bool o);
    bool isOver();
    bool isOver(std::shared_ptr<Block> nextblock);
    //determines if the game is over

    bool isFilled(Coordinate cor) const;
    //determine is a cell is filled

    std::shared_ptr<Cell> &getCell(Coordinate c);
    void setObserver(std::shared_ptr<Observer> o);
    //attaches o to the observer lists of all cells

    void clear();
    //resets the board

    void resetScore();
    void setHighScore(int hc);
    int getHighScore();
    bool rowFilled(size_t x) const;
    //returns if a row is filled

    bool clearRow(int level);
    //clears all bottom rows that are full, and updates score

    void dropBlock(std::shared_ptr<Block> &block);
    //attach block to the vector droppedBlock

    void setNext(std::shared_ptr<Block> &nb);
    //updates nextBlock

    void setColor(Color col, Coordinate& cor);

    boardState getState() const;
    size_t getHeight() const;
    size_t getWidth() const;
    void noGraphics();
    bool ifGraphic();
    void setLevel(int num);
    void notifyObservers();
    
    friend std::ostream &operator<<(std::ostream &out, const Board &b);
    
    //extra feature
    void setPlayerName(std::string name);
};
#endif


