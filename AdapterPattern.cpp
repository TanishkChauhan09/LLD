#include<iostream>
#include<string>
using namespace std;

class IReports{
    public:
    virtual string getjson(const string &data) = 0; 
    virtual ~IReports(){}
};

class XMLdataprovider{
  public:
   string getXMLdata(const string &data)
   {
        size_t sep = data.find(':');
        string name = data.substr(0, sep);
        string id   = data.substr(sep + 1);
        // Build an XML representation
        return "<user>"
               "<name>" + name + "</name>"
               "<id>"   + id   + "</id>"
               "</user>";
   }  
};

class XMLdataproviderAdapter:public IReports{
    private:
     XMLdataprovider *adaptee;

     public:
     XMLdataproviderAdapter(XMLdataprovider *adaptee)
     {
         this->adaptee = adaptee;
     }

    string getjson(const string &data){

        string xml = adaptee->getXMLdata(data);

        // 2. Naïvely parse out <name> and <id> values
        size_t startName = xml.find("<name>") + 6;
        size_t endName   = xml.find("</name>");
        string name      = xml.substr(startName, endName - startName);

        size_t startId = xml.find("<id>") + 4;
        size_t endId   = xml.find("</id>");
        string id      = xml.substr(startId, endId - startId);

        // 3. Build and return JSON
        return "{\"name\":\"" + name + "\", \"id\":" + id + "}";

     }
};

class Client {
public:
    void getReport(IReports* report, string rawData) {
        cout << "Processed JSON: "
        << report->getjson(rawData)
        << endl;
    }
};

int main()
{
     // 1. Create the adaptee
    XMLdataprovider* xmlProv = new XMLdataprovider();

    // 2. Make our adapter
    IReports* adapter = new XMLdataproviderAdapter(xmlProv);

    // 3. Give it some raw data
    string rawData = "Rohan:65";

    // 4. Client prints the JSON
    Client* client = new Client();
    client->getReport(adapter, rawData);
    // → Processed JSON: {"name":"Alice", "id":42}

    // 5. Cleanup
    delete adapter;
    delete xmlProv;
    return 0;

}

