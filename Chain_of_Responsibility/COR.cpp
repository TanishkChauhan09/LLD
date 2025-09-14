#include <iostream>
using namespace std;

// Abstract Handler (Base Class)
class MoneyHandler {
protected:
    MoneyHandler *nextHandler;

public:
    MoneyHandler() {
        this->nextHandler = nullptr;
    }

    void setNextHandler(MoneyHandler *next) { 
        nextHandler = next; 
    }

    virtual void dispense(int amount) = 0;
};
