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

class ThousandHandler : public MoneyHandler {
private:
    int numNotes;

public:
    ThousandHandler(int numNotes) {
        this->numNotes = numNotes;
    }

    void dispense(int amount) override {
        int notesNeeded = amount / 1000;

        if(notesNeeded > numNotes) {
            notesNeeded = numNotes;
            numNotes = 0;
        }
        else {
            numNotes -= notesNeeded;
        }

        if(notesNeeded > 0)
            cout << "Dispensing " << notesNeeded << " x ₹1000 notes.\n";

        int remainingAmount = amount - (notesNeeded * 1000);
        if(remainingAmount > 0) {
            if(nextHandler != nullptr) nextHandler->dispense(remainingAmount);
            else {
                cout << "Remaining amount of " << remainingAmount << " cannot be fulfilled (Insufficinet fund in ATM)\n";
            }
        }
    }
};


// Concrete Handler for 500 Rs Notes
class FiveHundredHandler : public MoneyHandler {
private:
    int numNotes;

public:
    FiveHundredHandler(int numNotes) {
        this->numNotes = numNotes;    
    }

    void dispense(int amount) override {
        int notesNeeded = amount / 500;

        if(notesNeeded > numNotes) {
            notesNeeded = numNotes;
            numNotes = 0;
        }
        else {
            numNotes -= notesNeeded;
        }