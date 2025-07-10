#include <iostream>
using namespace std;

class MySQLDatabase {  // Low-level module
public:
    void saveToSQL(string data) {
        cout << "Executing SQL Query: INSERT INTO users VALUES('" << data << "');" << endl;
    }
};

class MongoDBDatabase {  // Low-level module
public:
    void saveToMongo(string data) {
        cout << "Executing MongoDB Function: db.users.insert({name: '" << data << "'})" << endl;
    }
};

class UserService {  // High-level module (Tightly coupled)
private:
    MySQLDatabase sqlDb;  // Direct dependency on MySQL
    MongoDBDatabase mongoDb;  // Direct dependency on MongoDB

public:
    void storeUserToSQL(string user) {
        // MySQL-specific code
        sqlDb.saveToSQL(user);  
    }

    void storeUserToMongo(string user) {
        // MongoDB-specific code
        mongoDb.saveToMongo(user);  
    }
};

int main() {
    // High-level module depends directly on low-level modules
    // This violates the Dependency Inversion Principles (DIP)
    // because high-level modules should not depend on low-level modules directly.
    // Both should depend on abstractions.
    // 
    UserService service;
    service.storeUserToSQL("Rohan");
    service.storeUserToMongo("Sohan");
}
