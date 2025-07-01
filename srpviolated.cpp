#include <iostream>
#include <vector>

using namespace std;

class products{
    public:
        string name;
        double price;
    products(string name,double price)
    {
        this->name = name;
        this->price = price;
    }    
};

class shoppingcart{
    private:
    vector<products*>Products;
    public:
    void addproduct(products *p)
    {
        Products.push_back(p);
    }
     
    const vector<products*> &getproducts(){
        return Products;
    } 
    
    double calculatetotal()
    {
        double total=0;

        for(auto p:Products)
        {
            total+=p->price;
        }
        return total;
    }

    void printinvoice()
    {
        cout<<"cart products invoice:"<<endl;
        for(auto p:Products)
        {
            cout<< p->name <<" - Rs."<< p->price <<endl;
        }

        cout<<"Total: "<<calculatetotal();
    }

    void savetodatabase()
    {
        cout<<"Saving in a database";
    }

    
};

int main()
{
    shoppingcart* cart = new shoppingcart();
    cart->addproduct(new products("USB cable",95.80));
    cart->addproduct(new products("Mobile",160000.95));

    cout<<cart->calculatetotal()<<endl;
    cart->printinvoice();
    cout<<"\n";
    cart->savetodatabase();

}