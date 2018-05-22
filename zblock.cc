#include "zblock.h"
#include "block.h"
#include "coordinate.h"
#include <vector>
#include <memory>
#include "color.h"
using namespace std;

Zblock::Zblock(std::shared_ptr<Board>theBoard, bool heavy, size_t level):Block {theBoard,heavy, 2, level}{
    init();
}

void Zblock::init(){
    color = Color::Z;
    bottomLeftRef.x = 0;
    bottomLeftRef.y = theBoard->getHeight() - 3 - initialHeight;
    coords = {
        {Coordinate{0,1}, Coordinate{1,1},Coordinate{1,0}, Coordinate{2,0}},
        {Coordinate{0,0}, Coordinate{0,1},Coordinate{1,1}, Coordinate{1,2}},
    };
    for (auto &c: coords){
        for (auto &cc: c){
            cc.x += bottomLeftRef.x;
            cc.y += bottomLeftRef.y;
        }
    }
}

shared_ptr<Block> Zblock::clone(){
    auto p = make_shared<Zblock>(*this);
    return p;
}
