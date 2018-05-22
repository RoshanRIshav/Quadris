#ifndef OBSERVER_H
#define OBSERVER_H
#include "color.h"
class Subject;
class Cell;
class Board;

class Observer {
public:
	void notify(Subject &whoFrom);
	virtual void notify(Cell &whoFrom) = 0;
	virtual void notify(Board &whoFrom) = 0;
	virtual void modifyPreviewBoard(Color NewBlock) = 0;
	virtual ~Observer() = default;
};
#endif

