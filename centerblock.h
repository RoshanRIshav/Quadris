#ifndef CENTERBLOCK_H
#define CENTERBLOCK_H
#include "block.h"

class Centerblock: public Block{
    public:
        Centerblock(std::shared_ptr<Board>theBoard, bool heavy, size_t level);
        std::shared_ptr<Block> clone() override;
        void init() override;
};
#endif
