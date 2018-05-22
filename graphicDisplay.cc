#include <iostream>
#include <string>
#include "graphicDisplay.h"
#include "subject.h"
#include "board.h"
#include "cell.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(int row, int col, int winSize): rows{row + scoreNextPadding}, cols{col}, winSize{winSize}{
    cellWidth = 184/cols;   //Do not change
    cellHeight = 500/rows;  //Do not change
    levelToDisplay = "Level: " + to_string(level);
    scoreToDisplay = "Score: " + to_string(score);
    hiScoreToDisplay = "HiScore: " + to_string(hiScore);
    //The Window
    xw.fillRectangle(0, 0, 300, 600, Xwindow::Black);
    //The Scoreboard
    xw.drawString(0 , 1 * cellHeight, levelToDisplay, Xwindow::Green);
    xw.drawString(0, 2 * cellHeight, scoreToDisplay, Xwindow::Green);
    xw.drawString(0, 3 * cellHeight, hiScoreToDisplay, Xwindow::Green);
    //Game Area
    //Now the co-ord 0,0 corresponds to 5, 0
    //and so on. 5, 10 is the right most cell of the first row

    xw.fillRectangle(0, 90, cols *cellWidth, 20 * cellHeight,Xwindow::Orange);
    xw.fillRectangle(0, 90, cols *cellWidth, cellHeight,Xwindow::White);
    xw.fillRectangle(0, 375, cols *cellWidth, cellHeight,Xwindow::White);
}

void GraphicsDisplay::notify(Cell &whoNotified){
    Color whichColour = whoNotified.getColor();
    Coordinate coord = whoNotified.getCoord();
    if(whichColour == Color::I){
        xw.fillRectangle(coord.x * cellWidth, (((rows - scoreNextPadding) - coord.y) + rowOffset) * cellHeight, cellWidth - 1, cellHeight - 1, Xwindow::White);
    }
    else if(whichColour == Color::J){
        xw.fillRectangle(coord.x * cellWidth, (((rows - scoreNextPadding) - coord.y) + rowOffset) * cellHeight, cellWidth - 1, cellHeight - 1, Xwindow::Red);
    }
    else if(whichColour == Color::L){
        xw.fillRectangle(coord.x * cellWidth, (((rows - scoreNextPadding) - coord.y) + rowOffset) * cellHeight, cellWidth- 1, cellHeight- 1, Xwindow::Green);
    }
    else if(whichColour == Color::O){
        xw.fillRectangle(coord.x * cellWidth, (((rows - scoreNextPadding) - coord.y) + rowOffset) * cellHeight, cellWidth - 1, cellHeight - 1, Xwindow::Blue);
    }
    else if(whichColour == Color::S){
        xw.fillRectangle(coord.x * cellWidth, (((rows - scoreNextPadding) - coord.y) + rowOffset) * cellHeight, cellWidth- 1, cellHeight - 1, Xwindow::Magenta);
    }
    else if(whichColour == Color::Z){
        xw.fillRectangle(coord.x * cellWidth, (((rows - scoreNextPadding) - coord.y) + rowOffset) * cellHeight, cellWidth - 1, cellHeight - 1, Xwindow::Yellow);
    }
    else if(whichColour == Color::T){
        xw.fillRectangle(coord.x * cellWidth, (((rows - scoreNextPadding) - coord.y) + rowOffset) * cellHeight, cellWidth - 1, cellHeight - 1, Xwindow::Cyan);
    }
    else if(whichColour == Color::C){
        xw.fillRectangle(coord.x * cellWidth, (((rows - scoreNextPadding) - coord.y) + rowOffset) * cellHeight, cellWidth - 1, cellHeight - 1, Xwindow::Brown);
    }
    else if(whichColour == Color::H){
        xw.fillRectangle(coord.x * cellWidth, (((rows - scoreNextPadding) - coord.y) + rowOffset) * cellHeight, cellWidth - 1, cellHeight - 1, Xwindow::Black);
    }
    else if(whichColour == Color::Empty){
        xw.fillRectangle(coord.x * cellWidth, (((rows - scoreNextPadding) - coord.y) + rowOffset) * cellHeight, cellWidth - 1, cellHeight - 1, Xwindow::Orange);
    }
}

void GraphicsDisplay::modifyPreviewBoard(Color NewBlock){
    int index;
    if(NewBlock == Color::I) {
        index = 0;
        for(int i = 0; i < 4; i++){
            xw.fillRectangle(previewBlocks[index][i].y * cellWidth, (previewBlocks[index][i].x) * cellHeight, cellWidth - 1, cellHeight - 1, Xwindow::White);
        }
    }
    else if (NewBlock == Color::J) {
        index = 1;
        for(int i = 0; i < 4; i++){
            xw.fillRectangle(previewBlocks[index][i].y  * cellWidth, (previewBlocks[index][i].x) * cellHeight, cellWidth - 1, cellHeight - 1, Xwindow::Red);
        }
    }
    else if(NewBlock == Color::L) {
        index = 2;
        for(int i = 0; i < 4; i++){
            xw.fillRectangle(previewBlocks[index][i].y * cellWidth, (previewBlocks[index][i].x) * cellHeight, cellWidth - 1, cellHeight - 1, Xwindow::Green);
        }
    }
    else if(NewBlock == Color::O){
        index = 3;
        for(int i = 0; i < 4; i++){
            xw.fillRectangle(previewBlocks[index][i].y  * cellWidth, (previewBlocks[index][i].x) * cellHeight, cellWidth - 1, cellHeight - 1, Xwindow::Blue);
        }
    }
    else if (NewBlock == Color::S){
        index = 4;
        for(int i = 0; i < 4; i++){
            xw.fillRectangle(previewBlocks[index][i].y  * cellWidth, (previewBlocks[index][i].x) * cellHeight, cellWidth - 1, cellHeight - 1, Xwindow::Magenta);
        }
    }
    else if (NewBlock == Color::Z) {
        index = 5;
        for(int i = 0; i < 4; i++){
            xw.fillRectangle(previewBlocks[index][i].y  * cellWidth, (previewBlocks[index][i].x) * cellHeight, cellWidth - 1, cellHeight - 1, Xwindow::Yellow);
        }
    }
    else if (NewBlock == Color::T) {
        index = 6;
        for(int i = 0; i < 4; i++){
            xw.fillRectangle(previewBlocks[index][i].y * cellWidth, (previewBlocks[index][i].x) * cellHeight, cellWidth - 1, cellHeight - 1, Xwindow::Cyan);
        }
    }

}

void GraphicsDisplay::notify(Board &whoNotified){
    xw.fillRectangle(0, 0, 500, 80, Xwindow::Black);
    boardState currState = whoNotified.getState();
    Color nextBlock = currState.getColor();
    Score currScore = currState.getScore();
    score = currScore.getCurrentScore();
    hiScore = currScore.getHighScore();
    level = currState.getLevel();
    isFull = currState.isOver();
    levelToDisplay = "Level: " + to_string(level);
    scoreToDisplay = "Score: " + to_string(score);
    hiScoreToDisplay = "HiScore: " + to_string(hiScore);
    string name = currState.getPlayerName();
    player = "Player: " + name;

    xw.drawString(0 , 1 * cellHeight, levelToDisplay, Xwindow::Green);
    xw.drawString(0, 2 * cellHeight, scoreToDisplay, Xwindow::Green);
    xw.drawString(0, 3 * cellHeight, hiScoreToDisplay, Xwindow::Green);
    if(name != "noNameSupplied"){
        xw.drawString(0, 4 * cellHeight, player, Xwindow::Green);
    }
    xw.drawString(0, 27 * cellHeight, nextToDisplay, Xwindow::Green);

    //Refresh the bottom of the board and draw the next block;
    if(isFull){
        xw.fillRectangle(0, 0, winSize, winSize, Xwindow::Black);
        for(int i = 0; i < rows; i++){
            if(i >= 5 && i <= 23){
                for(int j = 0; j < cols + 1; j++){
                    if(i >= 5 && j < 13){
                        if(i == 5){
                            if(j != 3 && j != 5){
                                xw.fillRectangle(j * cellWidth, i * cellHeight, cellWidth/3, cellHeight/3, Xwindow::White);
                            }
                        }
                        if(i == 6){
                            if((j == 0 || j >= 6) && j < 10){
                                xw.fillRectangle(j * cellWidth, i * cellHeight, cellWidth/3, cellHeight/3, Xwindow::White);
                            }
                        }
                        if(i == 7){
                            xw.fillRectangle(j * cellWidth, i * cellHeight, cellWidth/3, cellHeight/3, Xwindow::White);
                        }
                        if(i == 8){
                            if(j != 1 && j != 4 && j < 10){
                                xw.fillRectangle(j * cellWidth, i * cellHeight, cellWidth/3, cellHeight/3, Xwindow::White);
                            }
                        }
                        if(i == 9){
                            if(j != 4 && j != 7){
                                xw.fillRectangle(j * cellWidth, i * cellHeight, cellWidth/3, cellHeight/3, Xwindow::White);
                            }
                        }
                        if(i == 9 && j == 2){
                            xw.fillRectangle(j * cellWidth, i * cellHeight, cellWidth/3, cellHeight/3, Xwindow::White);

                        }
                    }

                    if(i >= 13 && i <= 17){
                        if(j == 0){
                            xw.fillRectangle(j * cellWidth, i * cellHeight, cellWidth/3, cellHeight/3, Xwindow::Red);
                        }

                        if(i == 13){
                            if(j != 4)
                                xw.fillRectangle(j * cellWidth, i * cellHeight, cellWidth/3, cellHeight/3, Xwindow::Red);
                        }
                        if(i == 14 || i == 16){
                            if(j != 1 && j != 4 && j != 7 && j != 8 && j != 10){
                                xw.fillRectangle(j * cellWidth, i * cellHeight, cellWidth/3, cellHeight/3, Xwindow::Red);
                            }
                        }
                        if(i == 15){
                            if( j != 1 && j != 4){
                                xw.fillRectangle(j * cellWidth, i * cellHeight, cellWidth/3, cellHeight/3, Xwindow::Red);
                            }
                        }
                        if(i == 17){
                            if(j != 3 && j != 5 && j != 10){
                                xw.fillRectangle(j * cellWidth, i * cellHeight, cellWidth/3, cellHeight/3, Xwindow::Red);
                            }
                        }
                    }
                }
            }
        }
        for(int i = 0; i < rows; i++){
            if(i >= 5 && i <= 23){
                for(int j = 0; j < cols + 1; j++){
                    if(i >= 5 && j < 13){
                        if(i == 5){
                            if(j != 3 && j != 5){
                                xw.fillRectangle(j * cellWidth, i * cellHeight, cellWidth/3, cellHeight/3, Xwindow::Red);
                            }
                        }
                        if(i == 6){
                            if((j == 0 || j >= 6) && j < 10){
                                xw.fillRectangle(j * cellWidth, i * cellHeight, cellWidth/3, cellHeight/3, Xwindow::Red);
                            }
                        }
                        if(i == 7){
                            xw.fillRectangle(j * cellWidth, i * cellHeight, cellWidth/3, cellHeight/3, Xwindow::Red);
                        }
                        if(i == 8){
                            if(j != 1 && j != 4 && j < 10){
                                xw.fillRectangle(j * cellWidth, i * cellHeight, cellWidth/3, cellHeight/3, Xwindow::Red);
                            }
                        }
                        if(i == 9){
                            if(j != 4 && j != 7){
                                xw.fillRectangle(j * cellWidth, i * cellHeight, cellWidth/3, cellHeight/3, Xwindow::Red);
                            }
                        }
                        if(i == 9 && j == 2){
                            xw.fillRectangle(j * cellWidth, i * cellHeight, cellWidth/3, cellHeight/3, Xwindow::Red);

                        }
                    }

                    if(i >= 13 && i <= 17){
                        if(j == 0){
                            xw.fillRectangle(j * cellWidth, i * cellHeight, cellWidth/3, cellHeight/3, Xwindow::White);
                        }

                        if(i == 13){
                            if(j != 4)
                                xw.fillRectangle(j * cellWidth, i * cellHeight, cellWidth/3, cellHeight/3, Xwindow::White);
                        }
                        if(i == 14 || i == 16){
                            if(j != 1 && j != 4 && j != 7 && j != 8 && j != 10){
                                xw.fillRectangle(j * cellWidth, i * cellHeight, cellWidth/3, cellHeight/3, Xwindow::White);
                            }
                        }
                        if(i == 15){
                            if( j != 1 && j != 4){
                                xw.fillRectangle(j * cellWidth, i * cellHeight, cellWidth/3, cellHeight/3, Xwindow::White);
                            }
                        }
                        if(i == 17){
                            if(j != 3 && j != 5 && j != 10){
                                xw.fillRectangle(j * cellWidth, i * cellHeight, cellWidth/3, cellHeight/3, Xwindow::White);
                            }
                        }
                    }
                }
            }
        }
        xw.fillRectangle(0, 0, winSize, winSize, Xwindow::Black);
        xw.fillRectangle(0, 90, cols *cellWidth, 20*cellHeight,Xwindow::Orange);
        xw.fillRectangle(0, 90, cols *cellWidth, cellHeight,Xwindow::White);
        xw.fillRectangle(0, 375, cols *cellWidth, cellHeight,Xwindow::White);

    }
    else{
        for(int i = 27; i < rows + 2; i++){
            for(int j = 0; j < 4; j++){
                xw.fillRectangle(j * cellWidth, i * cellHeight, cellWidth, cellHeight, Xwindow::Black);
            }
        }
        modifyPreviewBoard(nextBlock);
    }
}

