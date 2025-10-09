
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


class PercentageDiscountStrategy : public DiscountStrategy {
private:
    double percent;
public:
    PercentageDiscountStrategy(double pct) {
        percent = pct;
    }
    double calculate(double baseAmount) override {
        return (percent / 100.0) * baseAmount;
    }
};

class PercentageWithCapStrategy : public DiscountStrategy {
private:
    double percent;
    double cap;
public:
    PercentageWithCapStrategy(double pct, double capVal) {
        percent = pct;
        cap = capVal;
    }
    double calculate(double baseAmount) override {
        double disc = (percent / 100.0) * baseAmount;
        if (disc > cap) {
            return cap;
        }
        return disc;
    }
};


enum StrategyType {
    FLAT,
    PERCENT,
    PERCENT_WITH_CAP
};

// ----------------------------
// DiscountStrategyManager (Singleton)
// ----------------------------
class DiscountStrategyManager {
private:
    static DiscountStrategyManager* instance;
    DiscountStrategyManager() {}
    DiscountStrategyManager(const DiscountStrategyManager&) = delete;
    DiscountStrategyManager& operator=(const DiscountStrategyManager&) = delete;
public:
    static DiscountStrategyManager* getInstance() {
        if (!instance) {
            instance = new DiscountStrategyManager();
        }
        return instance;
    }
    
};