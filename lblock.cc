#include "lblock.h"
#include "block.h"
#include "coordinate.h"
#include <vector>
#include <memory>
#include "color.h"
using namespace std;

Lblock::Lblock(std::shared_ptr<Board>theBoard, bool heavy, size_t level):Block {theBoard, heavy,2, level}{
    init();
}

void Lblock::init(){
    color = Color::L;

    bottomLeftRef.x = 0;
    bottomLeftRef.y = theBoard->getHeight()- 3 - initialHeight;
    coords = {
        {Coordinate{0,0}, Coordinate{1,0},Coordinate{2,0}, Coordinate{2,1}},
        {Coordinate{0,0}, Coordinate{1,0},Coordinate{0,1}, Coordinate{0,2}},
        {Coordinate{0,0}, Coordinate{0,1},Coordinate{1,1}, Coordinate{2,1}},
        {Coordinate{0,2}, Coordinate{1,2},Coordinate{1,1}, Coordinate{1,0}},
    };
    for (auto &c: coords){
        for (auto &cc: c){
            cc.x += bottomLeftRef.x;
            cc.y += bottomLeftRef.y;
        }

    }
}
shared_ptr<Block> Lblock::clone(){
    auto p = make_shared<Lblock>(*this);
    return p;
}

