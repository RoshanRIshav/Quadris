#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include "observer.h"
#include "coordinate.h"
#include "color.h"
#include "cell.h"
#include "board.h"
#include "color.h"
#include <vector>
#include <iostream>
#include <string>

class TextDisplay: public Observer {
 std::vector<std::vector<char>> theDisplay;
 std::vector<std::vector<char>> previewDisplay;
 int rows, cols, level = 0;
 //Dimensions of the previewBoard;
 int colsPreview = 4;
 int rowsPreview = 2;
 Color next;
 int score = 0;
 int hiScore = 0;
 bool isFull;
 std::string playerName;

 std::vector<std::vector<Coordinate>> previewBlocks = {
 	{Coordinate{1,0}, Coordinate{1,1},Coordinate{1,2}, Coordinate{1,3}}, //I
 	{Coordinate{0,0}, Coordinate{1,0},Coordinate{1,1}, Coordinate{1,2}}, //J
 	{Coordinate{0,2}, Coordinate{1,0},Coordinate{1,1}, Coordinate{1,2}}, //L
 	{Coordinate{0,0}, Coordinate{0,1},Coordinate{1,0}, Coordinate{1,1}}, //O
 	{Coordinate{0,1}, Coordinate{0,2},Coordinate{1,0}, Coordinate{1,1}}, //S
 	{Coordinate{0,0}, Coordinate{0,1},Coordinate{1,1}, Coordinate{1,2}}, //Z
 	{Coordinate{0,0}, Coordinate{0,1},Coordinate{0,2}, Coordinate{1,1}} //T
 };

 public:
  TextDisplay(int rows, int cols);
  void notify(Cell &whoNotified) override;
  void notify(Board &whoNotified) override;
  void modifyPreviewBoard(Color NewBlock);

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif

