#include "block.h"
#include "coordinate.h"
#include <vector>
#include <memory>
#include <iostream>
using namespace std;

Block::Block(shared_ptr<Board> theBoard, bool heavy, int initialHeight, size_t level):
    theBoard{theBoard}, heavy{heavy}, initialHeight{initialHeight}, level{level}{
    }

bool Block::canMove(int x, int y){
    for (auto &m: coords.at(rotateState)){
        if (theBoard->isFilled(Coordinate{m.x + x, m.y + y})) return false;
    }
    return true;
}

int Block::getLevel() const{
    return level;
}

void Block::cw(){
    int newRotateState = rotateState + 1;
    if (newRotateState >= coords.size()) newRotateState = 0;
    for (auto &coor: coords.at(newRotateState)){
        if (theBoard->isFilled(Coordinate{coor.x, coor.y})) return;
    }
    rotateState = newRotateState;
}

void Block::ccw(){
    int newRotateState = rotateState - 1;
    if (newRotateState < 0) newRotateState = coords.size() - 1;
    for (auto &coor: coords.at(newRotateState)){
        if (theBoard->isFilled(Coordinate{coor.x, coor.y})) return;
    }
    rotateState = newRotateState;
}

void Block::left(){
    if (canMove(-1, 0)){
        --bottomLeftRef.x;
        for (auto &m: coords){
            for (auto &n: m){
                --n.x;
            }
        }
    }
}

void Block::right(){
    if (canMove(1, 0)){
        ++bottomLeftRef.x;
        for (auto &m: coords){
            for (auto &n: m){
                ++n.x;
            }
        }
    }
}

void Block::down(){
    if (canMove(0, -1)){ 
        --bottomLeftRef.y;
        for (auto&m: coords){
            for (auto &n: m){
                --n.y;
            }
        }
    }
}

void Block::drop(){
    int i = 0;
    while(canMove(0, -1)){
        down();
        ++i;
    }
    bottomLeftRef.y -= i;

    highestY = 0;
    lowestY = theBoard->getHeight();
    for (auto &c: coords.at(rotateState)){
        if(c.y > highestY) highestY = c.y;
        if(c.y < lowestY) lowestY = c.y;
    }

    for (auto &c: coords.at(rotateState)){ 
        theBoard->setColor(color, c);
    }

}


void Block::clear(){
    for (auto &c: coords.at(rotateState)){
        shared_ptr<Cell> &cell= theBoard->getCell(Coordinate{c.x, c.y});
        shared_ptr<Cell> cw = make_shared<Cell>(*cell);
        cw->setColor(Color::Empty);

    }
}

void Block::draw(){
    for (auto &c: coords.at(rotateState)){
        shared_ptr<Cell> &cell = theBoard->getCell(Coordinate{c.x, c.y});

        shared_ptr<Cell> cw = make_shared<Cell>(*cell);
        cw->setColor(color);
    }
}


bool Block::isHeavy() const{
    return heavy;
}

Color Block::getColor(){
    return color;
}


void Block::setColor(Color c){
    color = c;
}

Coordinate Block::getblr() const{
    return bottomLeftRef;
}

shared_ptr<Block> Block::findBestPos(shared_ptr<Block> temp){
    shared_ptr<Block> bestBlock = temp->clone();
    shared_ptr<Block> b = temp->clone();
    shared_ptr<Block> r;
    shared_ptr<Block> c;
    int lowestDrop = 0;
    int leftBuffer = temp->getblr().x;
    int rightBuffer = theBoard->getWidth() - 1 - temp->getblr().x;
    for (int i = leftBuffer; i >= 0; --i){
        shared_ptr<Block>  c= b->clone();
        shared_ptr<Block>  r= b->clone();
        for (size_t i = 0; i < b->getCoord().size(); ++i){
            int drop = 0;
            while (b->canMove(0, -1)){
                ++drop;
                b->down();
            }
            if (drop > lowestDrop) {
                bestBlock = b->clone();
                lowestDrop = drop;
            }
            r->cw();
            b = r;
        }
        c->left();
        b=c;
    }

    b = temp->clone();
    for (int i = temp->getblr().x; i <= rightBuffer; ++i){
        shared_ptr<Block>  c= b->clone();
        shared_ptr<Block>  r= b->clone();
        for (size_t i = 0; i < b->getCoord().size(); ++i){
            int drop = 0;
            while (b->canMove(0, -1)){
                ++drop;
                b->down();
            }
            if (drop > lowestDrop) {
                bestBlock = b->clone();
                lowestDrop = drop;
            }
            r->cw();
            b = r;
        }
        c->right();
        b = c;
    }
    bestBlock->setColor(Color::H);
    return bestBlock; 
}

vector<vector<Coordinate>> Block::getCoord() const{
    return coords;
}

int Block::getHighestY() const{
    return highestY;
}

int Block::getLowestY() const{
    return lowestY;
}

void Block::sinkHighestY(){
    --highestY;
}

void Block::sinkLowestY(){
    --lowestY;
}

void Block::addLowestY(){
    ++lowestY;
}








