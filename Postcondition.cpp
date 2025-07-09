#include <iostream>

using namespace std;

// A Postcondition must be statisfied after a method is executed.
// Sub classes can strengthen the Postcondition but cannot weaken it.

class Car {
protected:
    int speed;    

public:
    Car() {
        speed = 0;
    }
    
    void accelerate() {
        cout << "Accelerating" << endl;
        speed += 20;
    }

    //PostCondition : Speed must reduce after brake
    virtual void brake() {
        cout << "Applying brakes" << endl;
        speed -= 20;
    }
};

// Subclass can strengthen postcondition - Does not violate LSP
class HybridCar : public Car {
private:
    int charge;

public:

    HybridCar() : Car() {
        charge = 0;
    }

    // PostCondition : Speed must reduce after brake
    // PostCondition : Charge must increase.(so post condition is strengthened)
    // This does not violate LSP as the client code can still use this method without any issues.
    // The client code excepts that the speed will reduce when brake is applied, and this is still true.
    void brake() {
        cout << "Applying brakes also charging little bit increased" << endl;
        speed -= 20;
        charge += 10;
    }
};


int main() {
    Car* hybridCar = new HybridCar();
    hybridCar->brake();  // Works fine: HybridCar reduces speed and also increases charge.

    //Client feels no difference in substituting Hybrid car in place of Car.

    return 0;
}
