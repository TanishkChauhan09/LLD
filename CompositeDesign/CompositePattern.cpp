#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

// Base interface for files and folders
class FileSystemItem{
   public:
   virtual ~FileSystemItem() {}
   virtual void ls(int indent = 0) = 0;            
   virtual void openAll(int indent = 0) = 0;      
   virtual int getSize() = 0;             

   // this is used to change or get the directory(pointer of that folder directly) that's why giving the name of the target folder in name
   virtual FileSystemItem* cd(const string& name) = 0; 

   virtual string getname() = 0;
   virtual bool isfolder() = 0;
};

// Leaf: File
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

    string getname() override {
        return name;
    }

    bool isfolder() override {
        return false;
    }
};

class Folder:public FileSystemItem{

   string name;
   vector<FileSystemItem*>children;

   public:
   Folder(string &na)
   {
       this->name = na;
   }
   ~Folder() override {
        for (auto c : children) delete c;
    }

    void add(FileSystemItem* item)
    {
        children.push_back(item);
    }

    void ls(int indent=0) override{
        
        for(auto child:children)
        {
            if(child->isfolder())
            {
                // string(indent,' ') :-  It creates a string of length indent, where every character is ' ' (a space).

                cout<< string(indent,' ')<<"+"<<child->getname()<<endl;
            }
            else{
                cout<< string(indent,' ')<<child->getname()<<endl;
            }
        }
    }

    void openAll(int indent=0) override{

        cout<< string(indent,' ')<<"+"<<name<<endl;
        
        for(auto child:children)
        {
            child->openAll(indent+4);
        }
    }

    int getSize() override
    {
        int total=0;
        for(auto child:children)
        {
            total+=child->getSize();
        }
        return total;
    }
    

    FileSystemItem *cd(const string &target) override
    {
         for(auto child : children)
         {
            if(child->isfolder() && child->getname() == target)
            return child;
         }

         return NULL;
    }

    string getname() override
    {
        return name;
    }

    bool isfolder() override
    {
        return true;
    }

};

int main(){
    
    string mainfoldername = "root";
    // if ,here i am directly passing the "root" like this in constructor then i have to make the (catching var) 
    // parameter as const ,oterwise if not write const , then i have to pass by storing value in a variable and then pass that variable in that constructor
    Folder *root = new Folder(mainfoldername);

    root->add(new file("file1.txt",1));
    root->add(new file("file2.txt",1));
    
    string folder2 = "docs";
    Folder *docs = new Folder(folder2);

    docs->add(new file("resume.pdf",2));
    docs->add(new file("notes.txt",3));
    
    root->add(docs);

    string image = "images";
    Folder *images = new Folder(image);
    images->add(new file("photos.jpeg",2));

    root->add(images);

    root->ls();
    cout<<"*********-------------**********"<<endl;
    docs->ls();
    cout<<"*********-------------**********"<<endl;

    root->openAll();
    cout<<"*********-------------**********"<<endl;
    docs->openAll();
    cout<<"*********-------------**********"<<endl;

    FileSystemItem *cwd = root->cd("docs");
    if(cwd!=NULL){
        cwd->ls();
    }
    else{
       cout<<"Could not cd int folder as it doesn't exist"<<endl;
    }
    
    cout<<"*********-------------**********"<<endl;
    cout<<root->getSize()<<endl;
    cout<<"*********-------------**********"<<endl;
    cout<<images->getSize()<<endl;


    // clean up
    delete images;
    delete docs;
    delete root;

    return 0;
}
