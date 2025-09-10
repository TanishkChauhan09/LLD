#include<iostream>
#include<string>

using namespace std;

class IImage { 
public:
    virtual void display() = 0;
    virtual ~IImage() = default;
};

class RealImage : public IImage {
    string filename;
public:
    RealImage(string file) {
        this->filename = file;
        // Heavy Operation
        cout << "[RealImage] Loading image from disk: " << filename << "\n";
    }

    void display() override {
        cout << "[RealImage] Displaying " << filename << "\n";
    }
};
    
class Imgageproxy : public IImage{
    RealImage* realimage;
    string filename;
    public:
    Imgageproxy(string file)
    {
        filename = file;
        realimage = nullptr;
    }

    void display() override{
        if(realimage == nullptr)
        {
            realimage = new RealImage(filename);
        }
        realimage->display();
    }
};

int main()
{
    IImage *image1 = new Imgageproxy("/photos/images/.jpej");
    image1->display();
    
}