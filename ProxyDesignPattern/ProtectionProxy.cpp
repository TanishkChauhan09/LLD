#include<iostream>
using namespace std;

class IDOCReader{
   public:
    virtual void unlockpdf(string files,string pass) = 0;
    virtual ~IDOCReader() = default;
};

class ReadDOCReader : public IDOCReader{
    public:
    void unlockpdf(string files,string pass)
    {
        if(pass == "1234")
        {
            cout << "PDF unlocked: " << files << endl;
        }
        else
        {
            cout << "Invalid password for: " << files << endl;
        }
    }
};

class User{
    public:
    string name;
    bool premiumMembership;

    User(string n,bool ispremium)
    {
        name = n;
        premiumMembership = ispremium;
    }
};

class ProxyReader : public IDOCReader{
    ReadDOCReader* realreader;
    User *user;

    public:
    ProxyReader(User *u)
    {
        user = u;
        realreader = new ReadDOCReader();
    }

    void unlockpdf(string files,string pass)
    {
        if(user->premiumMembership == false)
        {
            cout<<"Document access denied only Premium Members can unlock the pdf\n";
            return;
        }
        realreader->unlockpdf(files,pass);
    }
};


int main()
{
    User *user1 = new User("Rohan",false);
    ProxyReader *proxyReader = new ProxyReader(user1);
    proxyReader->unlockpdf(".docs/pdf","1234");

    User *user2 = new User("Sohan",true);
    proxyReader = new ProxyReader(user2);
    proxyReader->unlockpdf(".docs/pdf","2345");
}