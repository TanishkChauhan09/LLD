
#include <iostream>


using namespace std;

// ----------------------------
// Discount Strategy (Strategy Pattern)
// ----------------------------
class DiscountStrategy {
public:
    virtual ~DiscountStrategy() {}
    virtual double calculate(double baseAmount) = 0;
};

class FlatDiscountStrategy : public DiscountStrategy {
private:
    double amount;
public:
    FlatDiscountStrategy(double amt) {
        amount = amt;
    }
    double calculate(double baseAmount) override {
        return min(amount, baseAmount);
    }
};
