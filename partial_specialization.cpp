#include <iostream>
#include <vector>
#include <iterator>

// Partial specialization on a class
template<class T>
class A{
public:
    void foo(){
        std::cout << "Hello world" << std::endl;
    }
};

template<>
class A<int>{
public:
    void foo(){
        std::cout << "Hello int" << std::endl;
    }
};

// Partial specialization on a method
class B {
public:
    template<class T>
    void foo();
};

template<class T>
void B::foo(){
    std::cout << "Hello world" << std::endl;
}

template<>
void B::foo<int>(){
    std::cout << "Hello int" << std::endl;
}

int main() 
{
    B a;
    B b;

    a.foo<double>();
    b.foo<int>();

    return 0;
}

