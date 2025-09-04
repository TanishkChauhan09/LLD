#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

class FileSystemItem{
   public:
   virtual ~FileSystemItem() {}
   virtual void ls(int indent = 0) = 0;            
   virtual void openAll(int indent = 0) = 0;      
   virtual int getSize() = 0;                  
   virtual FileSystemItem* cd(const string& name) = 0; 
   virtual string getname(){} = 0;
   virtual bool isfolder(){} = 0;
};


class file:public FileSystemItem{
    private:
    string name;
    int size;

    public:
    file(string name,int size)
    {
        this->name = name;
        this->size=size;
    }
    void ls(int indent = 0) override {
        cout << string(indent, ' ') << name << "\n";
    }

    void openAll(int indent = 0) override {
        cout << string(indent, ' ') << name << "\n";
    }

    int getSize() override {
        return size;
    }

    FileSystemItem* cd(const string&) override {
        return nullptr;
    }

    string getName() override {
        return name;
    }

    bool isFolder() override {
        return false;
    }
};