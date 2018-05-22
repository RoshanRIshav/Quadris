#include "subject.h"
#include "observer.h"

Subject::Subject() {}

void Subject::attach(std::shared_ptr<Observer> o) {
	observers.emplace_back(o);
}

void Subject::detach(std::shared_ptr<Observer> o) {
	for (auto it = observers.begin(); it != observers.end();) {
		if ((*it).get() == o.get()) { observers.erase(it); }
		else { ++it; }
	}
}

void Subject::notifyObservers() {
	for (auto& i : observers) {
		i->notify(*this);
	}
}

Subject::~Subject() {}
