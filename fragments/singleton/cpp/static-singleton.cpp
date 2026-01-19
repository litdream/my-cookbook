#include <iostream>

class Singleton {
private:
    // Block constructors and assign-operators
    Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    // Block move semantics
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;
    
public:
    static Singleton& getInstance() {
        static Singleton inst;
        return inst;
    }
    
// Data    
private:
    int i;
    double d;

public:
    int getI() const { return i; }
    void setI(int v) { i = v; }
    double getD() const { return d; }
    void setD(double v) { d = v; }
};

void print_singleton() {
    using std::cout;
    using std::endl;

    cout << "Int: " << Singleton::getInstance().getI() << endl
         << "Doub: " << Singleton::getInstance().getD() << endl;
}

void single_set(int i, double d) {
    Singleton::getInstance().setI(i);
    Singleton::getInstance().setD(d);
}

int main() {
    single_set(3,3);
    print_singleton();

    single_set(5,5);
    print_singleton();

    return 0;
}
