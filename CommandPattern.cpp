#include <iostream>
using namespace std;


// observer pattern implememtation

class Icommand{
  public:
    virtual void execute()=0;
    virtual void undo()=0;

    virtual ~Icommand(){};
};

class Light{
    public:
    void ON()
    {
        cout<<"Light is ON"<<endl;
    }
    void OFF()
    {
        cout<<"Light is OFF"<<endl;
    }
};

class lightcommand:public Icommand{
    private:
       Light *light;

    public:
    // making the constructor to initialise the appliance to the command
    lightcommand(Light *l)
    {
        light = l;
    }

    void execute(){
        light->ON();
    }
    void undo(){
        light->OFF();
    }
};

class Fan{
    public:
    void ON()
    {
        cout<<"Fan is ON"<<endl;
    }
    void OFF()
    {
        cout<<"Fan is OFF"<<endl;
    }
};


class fancommand:public Icommand{
    private:
       Fan *fan;

    public:
    // making the constructor to initialise the appliance to the command
    fancommand(Fan *f)
    {
        fan = f;
    }

    void execute(){
        fan->ON();
    }
    void undo(){
        fan->OFF();
    }
};


class Remote{
    private:
    static const int totalbuttons=4;
    Icommand *buttons[totalbuttons];
    bool buttonpressed[totalbuttons];

    public:
    Remote()
    {
        for(int i=0;i<totalbuttons;i++)
        {
            buttons[i] = NULL;
            buttonpressed[i] = false;
        }
    }
    
    void setcommands(int idx,Icommand *cmd)
    {
        if(idx>=0 && idx<totalbuttons)
        {
            if(buttons[idx]==NULL)
            {
                delete buttons[idx];
            }
            buttons[idx] = cmd;
            buttonpressed[idx] = false;
        }
    }

    void pressbutton(int idx)
    {
        if(idx>=0 && idx<totalbuttons && buttons[idx]!=NULL)
        {
            if(buttonpressed[idx]==false)
            {
                buttons[idx]->execute();
            }
            else
            {
                buttons[idx]->undo();
            }
            buttonpressed[idx] = !buttonpressed[idx];
        }
        else
        {
            cout<<"You pressed an invalid button"<<idx<<endl;
        }
    }

    ~Remote(){
        for(int i=0;i<totalbuttons;i++)
        {
            if(buttons[i]!=NULL)
                delete buttons[i];
        }
    }

};


int main()
{
    
    Light *livingroomlight = new Light();
    Fan *normalfan = new Fan();

    Remote *remotecontroller = new Remote();

    remotecontroller->setcommands(0,new fancommand(normalfan));
    remotecontroller->setcommands(1,new lightcommand(livingroomlight));

    cout<<"-----Toggling for the FAN------"<<endl;
    remotecontroller->pressbutton(0);  // fan will be ON
    remotecontroller->pressbutton(0);  //fan will be OFF

    cout<<"-----Toggling for thr Light-----"<<endl;
    remotecontroller->pressbutton(1); //Light will be ON
    remotecontroller->pressbutton(1); //Light will ne OFF
    remotecontroller->pressbutton(1); //again, Light will be ON

    // clean up
    delete normalfan;
    delete livingroomlight;
    delete remotecontroller;

    return 0;
    
}