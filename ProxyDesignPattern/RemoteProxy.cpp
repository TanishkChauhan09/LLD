#include<iostream>
using namespace std;


class IDataService{
   public:
   virtual void fetchdata()=0;
   virtual ~IDataService(){};
};

class RealDataService:public IDataService{
   public:
   RealDataService()
   {
    //  cout<<"[Real Data Service] making the connection to the server"<<endl;
   }

   void fetchdata()
   {
     cout<<"[Real data Service] using the data to be fetched from the Server"<<endl;
   }
};

class ProxyDataService:public IDataService{
    RealDataService *realservice = new RealDataService();
    public:
    ProxyDataService()
    {
        cout<<"[Proxy Service connected] successfully"<<endl;
        
    }

    void fetchdata()
    {
        if(realservice==nullptr)
        {
            // realservice = new RealDataService();
        }
        else{
            cout<<"[Reusing the connection build already with the server]"<<endl;
        }
        realservice->fetchdata();
    }
};

int main()
{

    IDataService *dataservice = new ProxyDataService();
    dataservice->fetchdata();

}