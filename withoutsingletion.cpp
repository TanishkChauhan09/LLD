#include<iostream>

using namespace std;

class NoSingleton {
public:
    NoSingleton() {
        cout << "Singleton Constructor called. New Object created." << endl;
    }
};

int main() {
    NoSingleton* s1 = new NoSingleton();
    NoSingleton* s2 = new NoSingleton();

    // This will print 0,indicating that s1 and s2 are different instances
    // because we are not enforcing a singletion pattern.
    cout << (s1 == s2) << endl;
}