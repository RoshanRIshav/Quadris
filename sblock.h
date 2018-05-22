#ifndef SBLOCK_H
#define SBLOCK_H
#include "block.h"

class Sblock: public Block{
  public:
    Sblock(std::shared_ptr<Board>theBoard, bool heavy, size_t level);
    std::shared_ptr<Block> clone() override;
    void init() override;
 };
#endif
