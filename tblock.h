#ifndef TBLOCK_H
#define TBLOCK_H
#include "block.h"

class Tblock: public Block{
  public:
    Tblock(std::shared_ptr<Board>theBoard, bool heavy, size_t level);
    std::shared_ptr<Block> clone() override;
    void init() override;
};
#endif
