#ifndef OBLOCK_H
#define OBLOCK_H
#include "block.h"

class Oblock: public Block{
    public:
        Oblock(std::shared_ptr<Board>theBoard, bool isHeavy, size_t level);
        std::shared_ptr<Block> clone() override;
        void init() override;
};
#endif
