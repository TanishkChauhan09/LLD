
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
    DiscountStrategy* getStrategy(StrategyType type, double param1, double param2 = 0.0) const {
        if (type == StrategyType::FLAT) {
            return new FlatDiscountStrategy(param1);
        }
        if (type == StrategyType::PERCENT) {
            return new PercentageDiscountStrategy(param1);
        }
        if (type == StrategyType::PERCENT_WITH_CAP) {
            return new PercentageWithCapStrategy(param1, param2);
        }
        return nullptr;
    }
};

class Product {
private:
    string name;
    string category;
    double price;
public:
    Product(string name, string category, double price) {
        this->name = name;
        this->category = category;
        this->price = price;
    }
    string getName() {
        return name;
    }
    string getCategory() const {
        return category;
    }
    double getPrice() {
        return price;
    }
};

class CartItem {
private:
    Product* product;
    int quantity;
public:
    CartItem(Product* prod, int qty) {
        product = prod;
        quantity = qty;
    }
    double itemTotal() {
        return product->getPrice() * quantity;
    }
    const Product* getProduct() {
        return product;
    }
};

class Cart {
private:
    vector<CartItem*> items;
    double originalTotal;
    double currentTotal;
    bool loyaltyMember;
    string paymentBank;
public:
    Cart() {
        originalTotal = 0.0;
        currentTotal = 0.0;
        loyaltyMember = false;
        paymentBank = "";
    }
    void addProduct(Product* prod, int qty = 1) {
        CartItem* item = new CartItem(prod, qty);
        items.push_back(item);
        originalTotal += item->itemTotal();
        currentTotal  += item->itemTotal();
    }

    double getOriginalTotal() {
        return originalTotal;
    }

    double getCurrentTotal() {
        return currentTotal;
    }

    void applyDiscount(double d) {
        currentTotal -= d;
        if (currentTotal < 0) {
            currentTotal = 0;
        }
    }

    void setLoyaltyMember(bool member) {
        loyaltyMember = member;
    }

    bool isLoyaltyMember() {
        return loyaltyMember;
    }

    void setPaymentBank(string bank) {
        paymentBank = bank;
    }

    string getPaymentBank() {
        return paymentBank;
    }

    vector<CartItem*> getItems() {
        return items;
    }
};

class Coupon {
private:
    Coupon* next;
public:
    Coupon() {
        next = nullptr;
    }
    virtual ~Coupon() {
        if (next) {
            delete next;
        }
    }
    void setNext(Coupon* nxt) {
        next = nxt;
    }
    Coupon* getNext() {
        return next;
    }
    
    void applyDiscount(Cart* cart) {
        if (isApplicable(cart)) {
            double discount = getDiscount(cart);
            cart->applyDiscount(discount);
            cout << name() << " applied: " << discount << endl;
            if (!isCombinable()) {
                return;
            }
        }
        if (next) {
            next->applyDiscount(cart);
        }
    }
    virtual bool isApplicable(Cart* cart) = 0;
    virtual double getDiscount(Cart* cart) = 0;
    virtual bool isCombinable() {
        return true;
    }
    virtual string name() = 0;
};


class SeasonalOffer : public Coupon {
private:
    double percent;
    string category;
    DiscountStrategy* strat;
public:
    SeasonalOffer(double pct, string cat) {
        percent = pct;
        category = cat;
        strat = DiscountStrategyManager::getInstance()->getStrategy(StrategyType::PERCENT, percent);
    }
    ~SeasonalOffer() {
        delete strat;
    }
    bool isApplicable(Cart* cart) override {
        for (CartItem* item : cart->getItems()) {
            if (item->getProduct()->getCategory() == category) {
                return true;
            }
        }
        return false;
    }
    double getDiscount(Cart* cart) override {
        double subtotal = 0.0;
        for (CartItem* item : cart->getItems()) {
            if (item->getProduct()->getCategory() == category) {
                subtotal += item->itemTotal();
            }
        }
        return strat->calculate(subtotal);
    }
    bool isCombinable() override {
        return true;
    }
    string name() override {
        return "Seasonal Offer " + to_string((int)percent) + " % off " + category;
    }
};
