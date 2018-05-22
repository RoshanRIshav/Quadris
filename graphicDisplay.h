#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include <iostream>
#include <vector>
#include <string>
#include "observer.h"
#include "color.h"
#include "coordinate.h"
#include "window.h"


class Cell;
class Board;

class GraphicsDisplay: public Observer {
  const int rowOffset = 6;
  const int scoreNextPadding = 14;
  int rows, cols, winSize, cellHeight, cellWidth, level;
  int score, hiScore = 0;
  Color nextBlock;
  bool isFull;
  //ScoreCard fields
  std::string scoreToDisplay, hiScoreToDisplay, levelToDisplay, player;
  std::string nextToDisplay = "Next";


  Xwindow xw;
  std::vector<std::vector<Coordinate>> previewBlocks = {
 	{Coordinate{30,0}, Coordinate{30,1},Coordinate{30,2}, Coordinate{30,3}}, //I
 	{Coordinate{29,0}, Coordinate{30,0},Coordinate{30,1}, Coordinate{30,2}}, //J
 	{Coordinate{29,2}, Coordinate{30,0},Coordinate{30,1}, Coordinate{30,2}}, //L
 	{Coordinate{29,0}, Coordinate{29,1},Coordinate{30,0}, Coordinate{30,1}}, //O
 	{Coordinate{29,1}, Coordinate{29,2},Coordinate{30,0}, Coordinate{30,1}}, //S
 	{Coordinate{29,0}, Coordinate{29,1},Coordinate{30,1}, Coordinate{30,2}}, //Z
 	{Coordinate{29,0}, Coordinate{29,1},Coordinate{29,2}, Coordinate{30,1}}, //T
 };

 public:
  GraphicsDisplay(int rows, int cols, int winSize);
  void notify(Cell &whoNotified) override;
  void notify(Board &whoNotified) override;
  void modifyPreviewBoard(Color NewBlock);
  //std::vector<Coordinate> nextBlockPreview(); //Will use the field nextBlock;
};
#endif

