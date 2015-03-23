
#include <iostream>
#include <cstdlib>
#include <malloc.h>

template<class T>
class A {
public:
    static void foo(){
        std::cout << "foo" << std::endl;
    }
};

int main(){
    A<int>::foo();

    return 0;
}
