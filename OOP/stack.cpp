#include <iostream>
using namespace std;

class Stack {
     private: 
     int size;
     int* stk;
     int tos;
     static int stk_count;

    public : 

    Stack () { //DEFAULT CONSTRUCTOR
        size = 10;
        stk = new int[size];
        tos = -1;
        stk_count++;
    }

    Stack (int size) { //PARAMETERIZED CONSTRUCTOR
        this -> size = size;
        stk = new int [size];
        tos = -1;
        stk_count++;
    }

    //DEEP COPY

    Stack(const Stack& other) {
    // Copy normal variables
    size = other.size;
    tos = other.tos;

    // Create a NEW array
    stk = new int[size];

    // Copy elements from the other stack
    for (int i = 0; i <= tos; i++) {
        stk[i] = other.stk[i];
    }

    // This is a new Stack object
    stk_count++;
}

Stack& operator=(const Stack& other) {
//S1=S1
    if (this == &other) {
        return *this;
    }

    this ->stk = nullptr;
    this->size = other.size;
    this->tos = other.tos;

    //ALLOCATE NEW AREA IN MEMORY

    this->stk = new int [this->size];
    for (int i = 0; i<= other.tos; i++) {
        this-> stk[i] = other.stk[i];
    }
    return *this;
}

    int pop () {
        if (tos >= 0) {
            return stk [tos--];
        }
        else {
            cout << "Stack empty.\n";
        return -1;
        }
        
    }

    void push (int item) {
        if (tos < size-1) {
            stk[++tos] = item;
        }
        else {
            cout << "Stack is full. \n";
        }
    }

    static int getStkCount () {
        return stk_count;
    }

    int get_tos () {
        return tos;
    }

    int get_size() {
        return size;
    } 

    bool isEmpty() {
        return (tos == -1);
    }
    bool isFull () {
        return tos == size-1;
    }


    void set_size (int size) {

    }

    void print_stack () {
        if (tos == -1) {
            cout << "Stack empty.\n";
            return;
        }
            cout << "Stack elements: ";
            for (int i = 0; i <=tos ; i++) {
                cout << stk[i] << " ";
            }
            cout << endl;
    }

    ~Stack () {
        delete [] stk;
        stk = nullptr;
        stk_count--;
    }

};

int Stack :: stk_count = 0; //INITIALIZING STATIC VARIABLE (OUTSIDE OF CLASS)

int main () {
    Stack s1; //FOR DEFAULT CONSTRUCTOR
    Stack s2 (20); //FOR PARAMETERIZED CONSTRUCTOR

    for (int i = 1; i <= s1.get_size(); i++) {
        cout << "Pushing: " << i << " to S1 " << endl;
        s1.push (i);
    }

    s1.print_stack();
 for (int i = 0; i < s1.get_size(); i++) {

    if (!s1.isEmpty()) {
        int value = s1.pop();
        cout << "Popped " << value << " from S1\n";
    }
}

}