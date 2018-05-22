#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <memory>
#include "observer.h"
class Subject{
protected:
 std::vector<std::shared_ptr<Observer>> observers;

 public: 
 Subject();
 void attach(std::shared_ptr<Observer> o);
 void detach(std::shared_ptr<Observer> o);
 void virtual notifyObservers();
 virtual ~Subject() = 0;
};
#endif
