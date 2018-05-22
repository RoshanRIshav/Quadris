#ifndef BLOCK_H
#define BLOCK_H
#include <memory>
#include <vector>
#include "color.h"
#include "coordinate.h"
#include "board.h"

class Block {
 protected:
 std::shared_ptr<Board> theBoard;
 bool heavy;
 int initialHeight;
 int highestY;
 int lowestY;
 size_t level;
 std::vector<std::vector<Coordinate>> coords;
 Coordinate bottomLeftRef; //bottom-left reference point
 Color color;
 int rotateState = 0;
 Block(std::shared_ptr<Board> theBoard, bool heavy, int initialHeight, size_t level);

 public:
 virtual void init() = 0;
 Coordinate getblr() const;
 void cw();
 void ccw();
 bool canMove(int x, int y);
 void left();
 void right();
 void down();
 void drop();
 std::shared_ptr<Block> findBestPos(std::shared_ptr<Block> b);
 bool isHeavy() const;
 void clear();
 bool isEmpty() const;
 void draw();
 void undraw();
 int getLevel() const;
 void setColor(Color c);
 Color getColor();
 std::vector<std::vector<Coordinate>> getCoord() const;
 virtual std::shared_ptr<Block> clone() = 0;

 int getHighestY() const;
 int getLowestY() const;
 void sinkHighestY();
 void sinkLowestY();
 void addLowestY();
};
#endif


