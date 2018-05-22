#include "helper.h"
#include <stdexcept>
using namespace std;

void blockMove(shared_ptr<Block> block, commandType command) {
    switch (command) {
	case(commandType::left): block->left();break;
	case(commandType::right):  block->right();break;
	case(commandType::clockwise): block->cw(); break;
	case(commandType::counterclockwise): block->ccw(); break;
	case(commandType::down):block->down(); break;
	default: return;
	}
}

shared_ptr<Block> replace(commandType command, Level& level, shared_ptr<Board> theBoard) {
	int l = level.getLevel();
	bool b = level.isHeavy();
	switch (command) {
	case(commandType::I): return make_shared<Iblock>(theBoard, b, l);
	case(commandType::J): return make_shared<Jblock>(theBoard, b, l);
	case(commandType::L): return make_shared<Lblock>(theBoard, b, l);
	case(commandType::O): return make_shared<Oblock>(theBoard, b, l);
	case(commandType::S): return make_shared<Sblock>(theBoard, b, l);
	case(commandType::Z): return make_shared<Zblock>(theBoard, b, l);
	case(commandType::T): return make_shared<Tblock>(theBoard, b, l);
	default: throw(out_of_range("Wrong Command"));	}
}

