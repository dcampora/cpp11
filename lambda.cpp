
#include <iostream>  // cout, endl
#include <algorithm> // for_each
#include <vector>    // vector, begin, end
#include <typeinfo>

void report_square(int i) {
  std::cout << "The square of " << i << " is " << i*i << std::endl;
}

class ReportSquare {
public:
    ReportSquare() = default;
    // ReportSquare(const ReportSquare&) = delete; // With this it doesn't work - 
    // http://www.cplusplus.com/reference/algorithm/for_each/?kw=for_each

    ReportSquare(const ReportSquare&){ std::cout << "copy constructor" << std::endl; }

    void operator()(int i){
        std::cout << "The square of " << i << " is " << i*i << std::endl;
        // std::cout << i << " + 3 = " << i+3 << std::endl;
    }
};

int main() {
    std::vector<int> data{1,2,3,4,5};
    // for_each(begin(data), end(data), report_square);

    int a = 20;
    int b = 30;

    // How do scopes work in C++ / C++11?
    // for_each(begin(data), end(data),
    // [a] (int i) {
    //     std::cout << a << std::endl;
    // } );

    // ReportSquare reportFunctor;
    // for_each(begin(data), end(data), ReportSquare());


    // Python code:
    // data = [1,2,3,4,5]
    // user_input = int(raw_input("Please enter an integer: "))
    // for_each(data, lambda x: print("%d + %d = %d" % (x, user_input, x+user_input)))
    std::cout << "Please enter an integer: " << std::flush;
    std::cin >> b;
    std::cout << std::endl << "Your integer is " << b << std::endl;

    // std::cout << typeid(b).name() << std::endl;

    for_each(begin(data), end(data),
        ([&b] (int a) {
            std::cout << b << " + " << a << " = " << a + b << std::endl;
        }));
}


