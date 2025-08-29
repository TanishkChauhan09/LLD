#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class IBasePizaa{
    public:
    virtual string getdescription()=0;
    virtual double getcost()=0; 
};

class Margherita:public IBasePizaa{
    
    public:
    string getdescription()
    {
        return "Margherita Pizza"; 
    }
    
    double getcost()
    {
        return 100.0;
    }
};

class Vegdelight:public IBasePizaa{
    public:
    string getdescription()
    {
        return "VegDelight Pizza"; 
    }
    double getcost()
    {
        return 120.0;
    }
};


class IToppingDecrator:public IBasePizaa{
    public:
    IBasePizaa* basepizza;

    IToppingDecrator(IBasePizaa* base)
    {
        this->basepizza = base;
    }
};

class ExtraCheese:public IToppingDecrator{
    public:
    ExtraCheese(IBasePizaa* base) : IToppingDecrator(base){};

    string getdescription()
    {
        return basepizza->getdescription()+ " with Extra Cheese";
    }

    double getcost()
    {
        return basepizza->getcost()+ 20.0;
    }
};

class Mushroom:public IToppingDecrator{
    public:
    Mushroom(IBasePizaa* base) : IToppingDecrator(base){}; // deligating constructor syntax in c++11 and above

    string getdescription()
    {
        return basepizza->getdescription()+ " with fried Mushroom";
    }

    double getcost()
    {
        return basepizza->getcost()+ 30.0 ;
    }
};


class Onion_Tomato:public IToppingDecrator{
    public:
    Onion_Tomato(IBasePizaa* base) : IToppingDecrator(base){}; // deligating constructor syntax in c++11 and above

    string getdescription()
    {
        return basepizza->getdescription()+ " with veggies(Onion and Tomato)";
    }

    double getcost()
    {
        return basepizza->getcost()+ 25.0;
    }
};


int main()
{

    IBasePizaa* MargheritaPizza = new Margherita();

    cout<<"Your "<< MargheritaPizza->getdescription()<<endl;
    cout<<"Cost of Pizza is:"<< MargheritaPizza->getcost()<<endl;

    MargheritaPizza = new ExtraCheese(MargheritaPizza);
    cout<<"Your "<< MargheritaPizza->getdescription()<<endl;
    cout<<"Cost of Pizza is:" << MargheritaPizza->getcost()<<endl;

    MargheritaPizza = new Onion_Tomato(MargheritaPizza);
    cout<<"Your "<<MargheritaPizza->getdescription()<<endl;
    cout<< "Cost of Pizza is :"<<MargheritaPizza->getcost()<<endl;


    IBasePizaa* VegdelightPizza = new Vegdelight();
    cout<<"Your "<< VegdelightPizza->getdescription()<<endl;
    cout<<"Cost of Pizza is:"<<VegdelightPizza->getcost()<<endl;

    VegdelightPizza = new Mushroom(VegdelightPizza);
    cout<<"Your "<<VegdelightPizza->getdescription()<<endl;
    cout<<"Cost of Pizza is:"<<VegdelightPizza->getcost()<<endl;
}