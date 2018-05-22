#ifndef LBLOCK_H
#define LBLOCK_H
#include "block.h"

class Lblock: public Block {
  public:
    Lblock(std::shared_ptr<Board>theBoard, bool heavy, size_t level);
    std::shared_ptr<Block> clone() override; 
    void init() override;
};
#endif
