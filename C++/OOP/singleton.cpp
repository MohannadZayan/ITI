#include <iostream>
using namespace std;

class NetworkManager {
    private:
    NetworkManager () {
        cout << "Network initialized.\n";
    }

    public :
    static NetworkManager& getInstance () {
        static NetworkManager instance;
        return instance;
    }

    void send_data (const string & data) {
        cout << "Sending: " << data << endl;
    }
};

int main () {
    NetworkManager& n1 = NetworkManager :: getInstance();
    n1.send_data ("Login Request\n");

    NetworkManager& n2 = NetworkManager :: getInstance();
    n2.send_data ("Download Request\n");

    if (&n1 == &n2)
    cout <<"The two objects are identical.\n";
}