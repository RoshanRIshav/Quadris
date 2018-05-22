#ifndef CELL_H
#define CELL_H
#include "subject.h"
#include "color.h"
#include "coordinate.h"
#include <memory>

class Cell : public Subject {
	Coordinate cor;
	Color col = Color::Empty;
public:	
	Cell(Coordinate cor, Color col);
	void setColor(Color c);
	Coordinate getCoord() const ;
	Color getColor() const;
	bool isFilled() const;
	void notifyObservers();
};

#endif
