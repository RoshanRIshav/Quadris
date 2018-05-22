#include "sblock.h"
#include "coordinate.h"
#include <vector>
#include <memory>
#include "color.h"
using namespace std;

Sblock::Sblock(std::shared_ptr<Board>theBoard, bool heavy, size_t level):Block {theBoard, heavy, 2, level}{
    init();
}

void Sblock::init(){
    color = Color::S;
    bottomLeftRef.x = 0;
    bottomLeftRef.y = theBoard->getHeight() - 3 - initialHeight;
    coords = {
        {Coordinate{0,0}, Coordinate{1,0},Coordinate{1,1}, Coordinate{2,1}},
        {Coordinate{0,2}, Coordinate{0,1},Coordinate{1,1}, Coordinate{1,0}},
    };
    for (auto &c: coords){
        for (auto &cc: c){
            cc.x += bottomLeftRef.x;
            cc.y += bottomLeftRef.y;
        }

    }
}

shared_ptr<Block> Sblock::clone(){
     auto p = make_shared<Sblock>(*this);
      return p;
}
