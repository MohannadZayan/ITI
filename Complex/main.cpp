#include <iostream>
using namespace std;

class Complex {
     int real;
     int img;

     public : 
     Complex () : real(0), img(0) {
        cout << "Default constructor used" << endl;
     }
     Complex (int r) :real (r), img(r){
        cout << "One parameter constructor used" << endl;
     }
     Complex (int r, int i) :real(r), img(i) {
        cout << "Two parameter constructor used" << endl;
     }

     ~Complex() {cout << "Destructor used.\n";}

     void setReal(int r) {
        real = r;
     }
     void setImg (int i) {
        img = i;
     }

     int getReal () {
        return real;
     }

     int getImg() {
        return img;
     }



    void PrintComplex () {
        if (real == 0 && img ==0 ) {
            cout << 0;
        }
        else if (img == 0) {
            cout << real;
        }
        else if (real == 0) {
            cout << img << "i" << endl;
        }
        else {
            cout << real;
            if (img > 0)
            cout << " + " << img << "i" << endl;
            else
            cout << "-" << -img << "i" << endl;
        }
    }

    Complex Add (Complex other) {
        Complex result;

        result.real = (real + other.real);
        result.img = (img+other.img);

        return result;
    }

    Complex Sub (Complex other) {
        Complex result;

        result.real = (real-other.real);
        result.img = (img-other.img);

        return result;
    }

};

int main() {
    Complex c1;
    Complex c2(5);
    Complex c3(3, 4);

    cout << "C1 = ";
    c1.PrintComplex();
    cout << endl;

    cout << "C2 = ";
    c2.PrintComplex();
    cout << endl;

    cout << "C3 = ";
    c3.PrintComplex();
    cout << endl;

    Complex sum = c2.Add(c3);

    cout << "C2 + C3 = ";
    sum.PrintComplex();
    cout << endl;
}