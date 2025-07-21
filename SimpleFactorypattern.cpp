#include <iostream>

using namespace std;

// Product Class and subclasses
class Burger {
public:
    virtual void prepare() = 0;  // Pure virtual function
    virtual ~Burger() {}  // Virtual destructor
    
};

class BasicBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Basic Burger with bun, patty, and ketchup!" << endl;
    }
};

class StandardBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Standard Burger with bun, patty, cheese, and lettuce!" << endl;
    }
};

class PremiumBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Premium Burger with gourmet bun, premium patty, cheese, lettuce, and secret sauce!" << endl;
    }
};

class BasicWheatBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Basic Wheat Burger with bun, patty, and ketchup!" << endl;
    }
};

class StandardWheatBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Standard Wheat Burger with bun, patty, cheese, and lettuce!" << endl;
    }
};

class PremiumWheatBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Premium Wheat Burger with gourmet bun, premium patty, cheese, lettuce, and secret sauce!" << endl;
    }
};


// Factory and its concretions
class BurgerFactory {
public:
    Burger* createBurger(string& type){
        if(type== "basic") {
            return new BasicBurger();
        }
        else if (type == "standard") 
        {
            return new StandardBurger();
        } 
        else if (type == "premium") 
        {
            return new PremiumBurger();
        } 
        else 
        {
            cout << "Invalid burger type! " << endl;
            return nullptr;
        }

    }
};




int main() {
    string type = "premium";

    BurgerFactory* burgerfact = new BurgerFactory();
    Burger* burger = burgerfact->createBurger(type);
    if(burger)
    {
        burger->prepare();
        delete burger; // clean up 
        delete burgerfact; // clean up factory
    }
    return 0;
}



