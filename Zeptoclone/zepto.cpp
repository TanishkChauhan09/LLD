#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>

using namespace std;

/////////////////////////////////////////////
// Product & Factory
/////////////////////////////////////////////

class Product {
private:
    int sku;
    string name;
    double price;

public:
    Product(int id, string nm, double pr) {
        sku   = id;
        name  = nm;
        price = pr;
    }

    //Getters & Setters
    int getSku() {
        return this->sku;
    }

    string getName() {
        return this->name;
    }
    double getPrice() {
        return this->price;
    }
};

class ProductFactory {
public:
    static Product* createProduct(int sku) {
        // In reality product comes from DB
        string name;
        double price;

        if (sku == 101) {
            name  = "Apple";
            price = 20;
        }
        else if (sku == 102) {
            name  = "Banana";
            price = 10;
        }
        else if (sku == 103) {
            name  = "Chocolate";
            price = 50;
        }
        else if (sku == 201) {
            name  = "T-Shirt";
            price = 500;
        }
        else if (sku == 202) {
            name  = "Jeans";
            price = 1000;
        }
        else {
            name  = "Item" + to_string(sku);
            price = 100;
        }
        return new Product(sku, name, price);
    }
};

/////////////////////////////////////////////
// InventoryStore (Abstract) & DbInventoryStore
/////////////////////////////////////////////

class InventoryStore {
public:
    virtual ~InventoryStore() {}
    virtual void addProduct(Product* prod, int qty) = 0;
    virtual void removeProduct(int sku, int qty) = 0;
    virtual int checkStock(int sku) = 0;
    virtual vector<Product*> listAvailableProducts() = 0;
};

class DbInventoryStore : public InventoryStore {
private:
    map<int,int>* stock;             // SKU -> quantity
    map<int,Product*>* products;     // SKU -> Product*
public:
    DbInventoryStore() {
        stock = new map<int,int>();
        products = new map<int,Product*>();
    }
    ~DbInventoryStore() {
        for (auto it : *products) {
            delete it.second;
        }
        delete products;
        delete stock;
    }

    void addProduct(Product* prod, int qty) override {
        int sku = prod->getSku();
        if (products->count(sku) == 0) {
            // Does not exist
            (*products)[sku] = prod;
        } else {
            delete prod;
        }
        (*stock)[sku] += qty;
    }

    void removeProduct(int sku, int qty) override {
        if (stock->count(sku) == 0) 
            return;

        int currentQuantity = (*stock)[sku];
        int remainingQuantity = currentQuantity - qty;
        if (remainingQuantity > 0) {
            (*stock)[sku] = remainingQuantity;
        } else {
            stock->erase(sku);
        }
    }

    int checkStock(int sku) override {
        if (stock->count(sku) == 0) 
            return 0;

        return (*stock)[sku];
    }

    vector<Product*> listAvailableProducts() override {
        vector<Product*> available;
        for (auto it : *stock) {
            int sku = it.first;
            int qty = it.second;
            if (qty > 0 && products->count(sku)) {
                available.push_back((*products)[sku]);
            }
        }
        return available;
    }
};