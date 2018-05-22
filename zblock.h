#ifndef ZBLOCK_H
#define ZBLOCK_H
#include "block.h"

class Zblock: public Block{
  public:
    Zblock(std::shared_ptr<Board>theBoard, bool heavy, size_t level);
    std::shared_ptr<Block> clone() override;
    void init() override;
};
#endif
