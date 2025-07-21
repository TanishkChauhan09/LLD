#include <iostream>

using namespace std;

// Product Classes and it's subclasses

// Product 1
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

// Product 2
class GarlicBread
{
    public:
    virtual void prepare() = 0; //Purevirtual function
    virtual ~GarlicBread(){} //Virtual destructor
};

class BasicGarlicBread:public GarlicBread{
    public:
    void prepare() override {
        cout<<"Preparing Basic Garlic Bread with butter and garlic!"<<endl;
    }
};

class StandardGarlicBread:public GarlicBread{
    public:
    void prepare() override {
        cout<<"Preparing Standard Garlic Bread with butter,garlic and herbs!"<<endl;
    }
};

class PremiumGarlicBread:public GarlicBread{
    public:
    void prepare() override {
        cout<<"Preparing Premium Garlic Bread with butter,garlic,herbs and cheese!"<<endl;
    }
};

class BasicWheatGarlicBread:public GarlicBread{
    public:
    void prepare() override{
        cout<<"Preparing Basic Wheat Garlic Bread with butter and garlic!"<<endl;
    }
};

class StandardWheatGarlicBread:public GarlicBread{
    public:
    void prepare() override {
        cout<<"Preparing Standard Wheat Garlic Bread with butter,garlic and herbs!"<<endl;
    }
};

class PremiumWheatGarlicBread:public GarlicBread{
    public:
    void prepare() override {
        cout<<"Preparing Premium Wheat Garlic Bread with butter,garlic,herbs and cheese!"<<endl;   
    }
};


// Factory and its concretions
class BurgerFactory {
public:
    virtual Burger* createBurger(string& type) = 0;
    virtual GarlicBread* createGarlicBread(string type) = 0;
};

class SinghBurger : public BurgerFactory {
public:
    Burger* createBurger(string& type) override {
        if (type == "basic") {
            return new BasicBurger();
        } else if (type == "standard") {
            return new StandardBurger();
        } else if (type == "premium") {
            return new PremiumBurger();
        } else {
            cout << "Invalid burger type! " << endl;
            return nullptr;
        }
    }

    GarlicBread* createGarlicBread(string type) override
    {
        if(type == "basic")
        {
            return new BasicGarlicBread();
        }
        else if(type == "standard")
        {
            return new StandardGarlicBread();
        }
        else if(type == "premium")
        {
            return new PremiumGarlicBread();
        }
        else{
            cout<<"Invalid Garlic Bread type!"<<endl;
            return nullptr;
        }
    }
};

class KingBurger : public BurgerFactory {
public:
    Burger* createBurger(string& type) override {
        if (type == "basic") {
            return new BasicWheatBurger();
        } else if (type == "standard") {
            return new StandardWheatBurger();
        } else if (type == "premium") {
            return new PremiumWheatBurger();
        } else {
            cout << "Invalid burger type! " << endl;
            return nullptr;
        }
    }

    GarlicBread* createGarlicBread(string type) override
    {
        if(type == "basic")
        {
            return new BasicWheatGarlicBread();
        }
        else if(type == "standard")
        {
            return new StandardWheatGarlicBread();
        }
        else if(type == "premium")
        {
            return new PremiumWheatGarlicBread();
        }
        else{
            cout<<"Invalid Garlic Bread type!"<<endl;
            return nullptr;
        }
    }
};

int main() {
    string type = "standard";

    cout<<"BY using SinghBurger factory:"<<endl;

    BurgerFactory* myFactory = new SinghBurger();

    Burger* burger = myFactory->createBurger(type);
    burger->prepare();

    type="premium";

    GarlicBread* garlicbread = myFactory->createGarlicBread(type);
    garlicbread->prepare();
    
    delete burger; // clean up burger
    delete myFactory; // clean up factory
    delete garlicbread; //clean up garlic bread
    // Demonstrating another factory
    cout<<"BY using KingBurger factory:"<<endl;
    type = "basic";

    BurgerFactory* myFactory2 = new KingBurger();

    Burger* burger2 = myFactory2->createBurger(type);
    burger2->prepare();

    type = "standard";
    GarlicBread* garlicbread2 = myFactory->createGarlicBread(type);
    garlicbread2->prepare();

    delete burger2;
    delete myFactory2;
    delete garlicbread;

    return 0;
}



