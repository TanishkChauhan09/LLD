#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>


using namespace std;

// ----------------------------
// Data structure for payment details
// ----------------------------
struct PaymentRequest {
    string sender;
    string reciever;
    double amount;
    string currency;

    PaymentRequest(const string& sender, const string& reciever, double amt, const string& curr) {
        this->sender = sender;
        this->reciever = reciever;
        this->amount = amt;
        this->currency = curr;
    }
};

// ----------------------------
// Banking System interface and implementations (Strategy for actual payment logic)
// ----------------------------
class BankingSystem {
public:
    virtual bool processPayment(double amount) = 0;
    virtual ~BankingSystem() {}
};