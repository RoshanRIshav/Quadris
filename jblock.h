#ifndef JBLOCK_H
#define JBLOCK_H
#include "block.h"

class Jblock: public Block {
  public:
    Jblock(std::shared_ptr<Board>theBoard, bool heavy, size_t level);
    std::shared_ptr<Block> clone() override;    
    void init() override;
};
#endif
