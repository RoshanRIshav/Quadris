#ifndef HELPER_H
#define HELPER_H
#include <memory>
#include "block.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"
#include "board.h"
#include "commandInterpreter.h"
#include "level.h"

void blockMove(std::shared_ptr<Block>, commandType command);

std::shared_ptr<Block> replace(commandType command, Level& level, std::shared_ptr<Board> theBoard);

#endif
