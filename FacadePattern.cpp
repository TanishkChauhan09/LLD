#include<iostream>
using namespace std;

class PowerSupply{
    public:
    void providepower(){
      cout<<"Power Supply:Power started...."<<endl;
    }
};

class CoolingSystem{
    public:
    void startfans()
    {
        cout<<"Coolong System:Fans started...."<<endl;
    }
};

class CPU{
   public:
   void initialize(){
    cout<<"CPU:Initialization started...."<<endl;
   }
};

class Memory{
    public:
    void selftest(){
        cout<<"Memory:Self test passed...."<<endl;
    }
};

class HardDrive{
    public:
    void spinup(){
        cout<<"Hard Drive:Spinning up...."<<endl;
    }
};

class operatingSystem{
    public:
    void load(){
        cout<<"Operating System: Loading into memory...."<<endl;
    }
};

class BIOS{
    public:
    void boot(CPU &cpu,Memory &memory){
        cout<<"BIOS:Booting CPU and Memory checks...."<<endl;
        cpu.initialize();
        memory.selftest();
    } 
};

