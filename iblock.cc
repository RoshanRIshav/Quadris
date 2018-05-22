#include "iblock.h"
#include "block.h"
#include <vector>
#include <memory>
#include <iostream>
using namespace std;

Iblock::Iblock(std::shared_ptr<Board>theBoard, bool heavy, size_t level):Block {theBoard, heavy, 1, level}{
    init();
}

void Iblock::init(){
    color = Color::I;

    bottomLeftRef.x = 0;
    bottomLeftRef.y = theBoard->getHeight() - 3 - initialHeight;

    coords = {
        {Coordinate{0,0}, Coordinate{1,0},Coordinate{2,0}, Coordinate{3,0}},
        {Coordinate{0,0}, Coordinate{0,1},Coordinate{0,2}, Coordinate{0,3}},
    };
    for (auto &c: coords){
        for (auto &cc: c){
            cc.x += bottomLeftRef.x;
            cc.y += bottomLeftRef.y;
        } 
    }
}

shared_ptr<Block> Iblock::clone(){
 auto p = make_shared<Iblock>(*this);
 return p; 
}
