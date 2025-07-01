#include <iostream>
#include <vector>

using namespace std;

// Product class representing any item in eCommerce.
class products
{
    public:
    string name;
    double price;

    products(string name,double price)
    {
        this->name= name;
        this->price = price;
    }
};

//1. ShoppingCart: Only responsible for Cart related business logic.
class shoppingcart
{
    private:
    vector<products*> Products;   // Store heap-allocated products
    
    public:
    void addproduct(products* p){
      Products.push_back(p);
    }

    vector<products*> getproduct(){
      return Products;
    }

    //Calculates total price in cart. 
    double calculatetotal()
    {
        double total=0;

        for(auto p:Products)
        total += p->price;

        return total;
    }  

};

// 2. cartInvoiceprinter: Only responsible for printing invoices
class cartInvoiceprinter{
    private:
    shoppingcart* cart;
    public:
    cartInvoiceprinter(shoppingcart* cart)
    {
        this->cart = cart;
    }

    void printinvoice()
    {
        cout<<"Shopping cart invoice"<<endl;

        for(auto p:cart->getproduct())
        {
            cout<< p->price <<" -Rs "<< p->name<<endl;
        }
        cout<<"Total is:"<<cart->calculatetotal()<<endl;
    }
    
};

// 3. cartDBstorage: Only responsible for saving cart to DB
class cartDBstorage
{
    private:
    shoppingcart* cart;
    public:
    cartDBstorage(shoppingcart* cart)
    {
        this->cart = cart;
    }

    void savetoDB()
    {
        cout<<"Saving shopping cart into the Database...."<<endl;
    }
};

int main()
{
   shoppingcart* cart = new shoppingcart();
   cart->addproduct(new products("Laptop",250000.60));
   cart->addproduct(new products("Tablet",95000.98));

   cartInvoiceprinter* printin = new cartInvoiceprinter(cart);
   printin->printinvoice();

   cartDBstorage* cartdb = new cartDBstorage(cart);
   cartdb->savetoDB();
}