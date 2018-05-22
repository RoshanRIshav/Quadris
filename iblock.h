#ifndef IBLOCK_H
#define IBLOCK_H
#include "block.h"
#include "coordinate.h"
#include <memory>

class Iblock: public Block{
    public:
    Iblock(std::shared_ptr<Board>theBoard, bool isHeavy, size_t level);
    std::shared_ptr<Block> clone() override;
    void init() override;
};
#endif


