#include <iostream>
using namespace std;

class Vehicle {
    protected: 
    static int count;

    public: 
    Vehicle () {
        count ++;
        cout << "Vehicle constructor.\n";
    }

    virtual void move () const {
        cout << "Vehicle is moving.\n";
    }

    static int getCount() {
        return count;
    }

    virtual ~Vehicle() {
        cout << "Vehicle destructor.\n";
    }

};

int Vehicle :: count = 0;

// CAR

class Car : public Vehicle {
    public: 
    Car () {
        cout << "Car constructor.\n";
    }

    void move () const override {
        cout << "Car is driving.\n";
    }

    ~Car () {
        cout << "Car destructor.\n";
    }
};

class BMW : public Car {
    public :
    BMW() {
        cout << "BMW destructor.\n";
    }

    void move () const override
 {
    cout << "BMW is driving.\n";
 }

 ~BMW () {
    cout << "BMW Destructor.\n";
 }
};

//MOTORCYCLE

class Motorcycle : public Vehicle {
public:
    Motorcycle() {
        cout << "Motorcycle constructor.\n";
    }

    void move() const override {
        cout << "Motorcycle is riding on the road.\n";
    }

    ~Motorcycle() {
        cout << "Motorcycle destructor.\n";
    }
};

class Yamaha : public Motorcycle {
public:
    Yamaha() {
        cout << "Yamaha constructor.\n";
    }

    void move() const override {
        cout << "Yamaha is riding on the road.\n";
    }

    ~Yamaha() {
        cout << "Yamaha destructor.\n";
    }
};

class Plane : public Vehicle {
public:
    Plane() {
        cout << "Plane constructor.\n";
    }

    void move() const override {
        cout << "Plane is flying in the sky.\n";
    }

    ~Plane() {
        cout << "Plane destructor.\n";
    }
};

class Boeing : public Plane {
public:
    Boeing() {
        cout << "Boeing constructor.\n";
    }

    void move() const override {
        cout << "Boeing is flying in the sky.\n";
    }

    ~Boeing() {
        cout << "Boeing destructor.\n";
    }
};
int main() {

    BMW bmw;
    Yamaha yamaha;
    Boeing boeing;

    
    Vehicle* v1 = &bmw;
    Vehicle* v2 = &yamaha;
    Vehicle* v3 = &boeing;

    cout << "\nVehicle movements:\n";

    v1->move();
    v2->move();
    v3->move();

    cout << "\nTotal vehicles created: "
         << Vehicle::getCount() << endl;

    return 0;
}
