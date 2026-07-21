#include <iostream>
using namespace std;
class Geometry {
    protected:
    static int count;

    public:
    Geometry () {
        count ++;
        cout << "Geometry constructor.\n";
    }

    virtual double area() const {
        return 0.0;
    }

    static int getCount() {
        return count;
    }

    virtual ~Geometry () {
        cout << "Geometry destructor.\n";
    }


};
int Geometry :: count = 0;

class Rectangle : public Geometry {
    protected:
    double width;
    double length;

    public: 
    Rectangle (double w, double l) : width (w), length (l) {
        cout << "Rectangle constructor.\n";
    }

    double area () const override {
        return width * length;
    }

    ~Rectangle () {
        cout << "Rectangle destructor.\n";
    }
};
    class Square : public Rectangle {

        public : 
        Square (double side) : Rectangle (side, side) {
            cout << "Square constructor.\n";
        }

        double area () const override {
            return length * length;
        }

        ~Square () {
            cout << "Square destructor.\n";
        }
    };


int main () {
    Rectangle rectangle (5,3);
    Square square (4);

    Geometry* g1 = &rectangle;
    Geometry* g2 = &square;

    cout << "\nAreas:\n";

    cout << "Rectangle area: " << g1->area() << endl;
    cout << "Square area: " << g2-> area() << endl;

    cout <<"\nTotal Geometries created: " << Geometry :: getCount() << endl;

    return 0;
}
