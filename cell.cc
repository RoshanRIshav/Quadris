#include "cell.h"
using namespace std;

Cell::Cell(Coordinate cor, Color col) :cor{ cor }, col{ col } {}

void Cell::setColor(Color c) {
	col = c;
	notifyObservers();
}

Coordinate Cell::getCoord() const {
	return cor;
}

Color Cell::getColor() const {
	return col;
}

bool Cell::isFilled() const {
	if (col == Color::Empty) return false;
	return true;
}

void Cell::notifyObservers() {
    for (auto &i: observers) {i->notify(*this);}
}
