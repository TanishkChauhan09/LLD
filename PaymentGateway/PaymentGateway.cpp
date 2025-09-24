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

class PaytmBankingSystem : public BankingSystem {
public:
    PaytmBankingSystem() {}
    bool processPayment(double amount) override {
        // Simulate 20% success
            int r = rand() % 100;
            return r < 80;
    }
};

class RazorpayBankingSystem : public BankingSystem {
public:
    RazorpayBankingSystem() {}
    bool processPayment(double amount) override {
        cout << "[BankingSystem-Razorpay] Processing payment of " << amount << "...\n";
        // Simulate 90% success
        int r = rand() % 100;
        return r < 90;
    }
};

class PaymentGateway {
protected:
    BankingSystem* bankingSystem;
public:
    PaymentGateway() { 
        bankingSystem = nullptr;
    }
    virtual ~PaymentGateway() { 
        delete bankingSystem; 
    }

    // Template method defining the standard payment flow
    virtual bool processPayment(PaymentRequest* request) {
        if (!validatePayment(request)) {
            cout << "[PaymentGateway] Validation failed for " << request->sender << ".\n";
            return false;
        }
        if (!initiatePayment(request)) {
            cout << "[PaymentGateway] Initiation failed for " << request->sender << ".\n";
            return false;
        }
        if (!confirmPayment(request)) {
            cout << "[PaymentGateway] Confirmation failed for " << request->sender << ".\n";
            return false;
        }
        return true;
    }

    // Steps to be implemented by concrete gateways
    virtual bool validatePayment(PaymentRequest* request) = 0;
    virtual bool initiatePayment(PaymentRequest* request) = 0;
    virtual bool confirmPayment(PaymentRequest* request) = 0;
};


class PaytmGateway : public PaymentGateway {
public:
    PaytmGateway() {
        bankingSystem = new PaytmBankingSystem();
    }
    bool validatePayment(PaymentRequest* request) override {
        cout << "[Paytm] Validating payment for " << request->sender << ".\n";

        if (request->amount <= 0 || request->currency != "INR") {
            return false;
        }
        return true;
    }
};