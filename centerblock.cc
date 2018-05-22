#include "centerblock.h"
#include "block.h"
#include "coordinate.h"
#include <vector>
#include <memory>
#include "color.h"

Centerblock::Centerblock(std::shared_ptr<Board>theBoard, bool heavy, size_t level):Block {theBoard,heavy, 0, level}{
    init();
}

void Centerblock::init(){
    color = Color::C;
    bottomLeftRef.x = theBoard->getWidth()/2;
    bottomLeftRef.y = theBoard->getHeight() - 3 - initialHeight;
    coords = {{Coordinate{0,0}}};
    for (auto &c: coords){
        for (auto &cc: c){
            cc.x += bottomLeftRef.x;
            cc.y += bottomLeftRef.y;
        }
    }
    drop();
}

std::shared_ptr<Block> Centerblock::clone(){
}
