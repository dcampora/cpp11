
#include <iostream>

template<typename T>
class A {
public:
    mutable T a;

    A(T b){
        std::cout << "main class" << std::endl;
    }
};

template<typename T>
class A <T&> {
public:
    T& a;

    A(T& b) : a(b) {
        std::cout << "partial specialization" << std::endl;
    }
};

int main(int argc, char const *argv[])
{
    int i = 20;

    A<int> a{i};
    A<int&> b{i};

    // std::cout << "types: " << type(a) << ", " << type(b) << std::endl;

    // b.foo();

    return 0;
}