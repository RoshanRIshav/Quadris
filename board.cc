#include "board.h"
#include "block.h"
#include "textDisplay.h"
#include "color.h"
#include <stdexcept>
using namespace std;

boardState::boardState(Score s, Color c, int level, bool o, string name) :
    score{ s }, color{ c }, level{ level }, over{ o }, playerName{name} {
    }

Score boardState::getScore() { return score; }
Color boardState::getColor() { return color; }
int boardState::getLevel() { return level; }
bool boardState::isOver() { return over; }
string boardState::getPlayerName() {return playerName;}

    Board::Board(size_t r, size_t c, std::shared_ptr<TextDisplay> td, int level) : \
            r{ r }, c{ c }, td{ td }, level{ level } {
                theBoard.resize(r);
                for (size_t i = 0; i<r; i++) {
                    theBoard.at(i).resize(c);
                    for (size_t j = 0; j<c; j++) {
                        shared_ptr<Cell> ptr = make_shared<Cell>(Coordinate{j,i}, Color::Empty);
                        theBoard.at(i).at(j) = ptr;
                    }
                }
                notifyObservers();
            }

Board::~Board() {}

void Board::setOver(bool o) {
	over = o;
	notifyObservers();
}

bool Board::isOver() {
    return over;
}

bool Board::isOver(shared_ptr<Block> nextblock){
	if(over) {return true;}
	else if (!nextBlock->canMove(0,0)) {return true;}
	else {return over;}
}

bool Board::isFilled(Coordinate cor) const {
    if ((cor.x < 0)||(cor.x>=c)||(cor.y<0)||(cor.y>=r)) {return true;}
	else  {
            return theBoard.at(cor.y).at(cor.x)->isFilled();
   }    
}

shared_ptr<Cell> &Board::getCell(Coordinate c) {
    return theBoard.at(c.y).at(c.x);
}

void Board::setObserver(std::shared_ptr<Observer> o) {
    for (auto &i : theBoard) {
        for (auto &j : i) {
            j->attach(o);
        }
    }
}

void Board::clear() {
    for (auto &m : theBoard) {
        for (auto &n : m) {
            n->setColor(Color::Empty);
        }
    }
}

void Board::resetScore() {
	score.setCurrentScore(0);
}

void Board::setHighScore(int hc) {
    score.setHighScore(hc);
}

int Board::getHighScore() {
    return score.getHighScore();
}

bool Board::rowFilled(size_t x) const {
    for (auto &m : theBoard.at(x)) {
        if (!m->isFilled()) return false;
    }
    return true;
}

bool Board::clearRow(int level) {
    int row; //the row that is filled
    bool nothingtoclear = false; 
    int cleared = 0; //total number of cleared rows
    while(nothingtoclear == false) {
        for (size_t i = 0; i < r; ++i) {
            if (rowFilled(i)) {
                row = i;
                break;
            } else if (!rowFilled(i)&&(i==(r-1))) {
                nothingtoclear = true;
		break;
            }
        }
	
	if(nothingtoclear) break;	

        //changes the color of all rows above row, including row
        for (size_t i = row; i<r;++i){
	    if ((i + 1) < r) {
            	for (size_t j = 0; j < c; ++j) {
                	theBoard.at(i).at(j)->setColor(theBoard.at(i + 1).at(j)->getColor());
            	}
            }
            else {
             	for (size_t j = 0; j < c; ++j) {
                     if (theBoard.at(i).at(j)->getColor() != Color::Empty) {
                        theBoard.at(i).at(j)->setColor(Color::Empty);
                     }
       	         }
     	    }
	}

        //sink dropped blocks and update score if any block is completely cleared
        for (auto it = droppedBlock.begin(); it != droppedBlock.end();) {
	    if (((*it)->getHighestY() == row)&&((*it)->getLowestY() == row)) {
		//the block is left with only one row and we're clearing it
                score.addCurrentScore(((*it)->getLevel() + 1)*((*it)->getLevel() + 1));
		droppedBlock.erase(it);
            } 
            else if ((*it)->getLowestY() > row) { //the entire block is above the row being cleared
                (*it)->sinkHighestY();
		(*it)->sinkLowestY();
		++it;
            }
            else if (((*it)->getLowestY() <= row)&&((*it)->getHighestY() >= row)) {
     		//the row being cleared is above the lowest but below the highest
		(*it)->sinkHighestY();
		++it;
	    }
	    else { //the entire block is beneath the row being cleared (not affected)
            	++it;
	    }
        }
        ++cleared;
    }
   
    //updates the score
    if (cleared > 0) {
        score.addCurrentScore((cleared + level)*(cleared + level));
        //Scores earned by clearing rows
        
        notifyObservers();
    }
    

    for (size_t i = 0; i < c; ++i) {
        if (theBoard.at(r - buffer).at(i)->getColor() != Color::Empty) {
            over = true;
            break;
        }
    }

    return (cleared>0);
}

void Board::dropBlock(std::shared_ptr<Block> &block) {
    droppedBlock.emplace_back(block);
}

void Board::setNext(std::shared_ptr<Block> &nb) {
    nextBlock = nb;
    notifyObservers();
}

void Board::setColor(Color col, Coordinate& cor) {
    try {theBoard.at(cor.y).at(cor.x)->setColor(col);
    } catch(out_of_range) {}
}

boardState Board::getState() const {
    return { score, nextBlock->getColor(), level, over, playerName};
}

size_t Board::getHeight() const { return r; }

size_t Board::getWidth() const { return c; }

void Board::noGraphics() {
    ifgraphic = false;
}

bool Board::ifGraphic() {
    return ifgraphic;
}

void Board::setLevel(int num) {
    level = num;
    notifyObservers();
}

ostream &operator<<(std::ostream &out, const Board &b) {
    return out << *(b.td);
}

void Board::notifyObservers() {
    for (auto &i: observers) {i->notify(*this);}
}

//extra feature
void Board::setPlayerName(string name) {
    playerName = name;
}






