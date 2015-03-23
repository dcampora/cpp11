#include <iostream>         // cout, endl
#include <initializer_list> // initializer_list
#include <string>           // string

using std::string;

// A guinea-pig type to be used as a member of class A lower down
class X {
public:
  X(int)                        : n{"int     "} {}
  X(int, int)                        : n{"int int "} {}
  X(std::initializer_list<int>) : n{"initlist"} {}
  string n;
};

// A guinea-pig type to be used as a member of class A lower down
class Y {
public:
  Y(int)                        : n{"int     "} {}
  string n;
};

// A class with default-initialized members (a,b,c)
class A {
public:
  A(        ) : a{"OVERRIDE "} {}
  A(int     ) : b{"OVERRIDE "} {}
  A(int, int) : c{"OVERRIDE "} {}
  void report() const { 
    std::cout << a << " " << b << " " << c << "  " 
              << x.n << " " << y.n << std::endl; }
private:
  string a = "default a";   // Overridden by A()
  string b{"default b"};    // Overridden by A(int)
  string c = {"default c"}; // Overridden by A(int, int)
  // int d("default d"); // Error: direct-initialization syntax with parentheses

  X x = X(1,2);   // initializer_list wins overload resolution
  Y y{1};   // matches int in absence of initializer_list
};

int main() {
  A(   ).report();  // OVERRIDE default b default c initializer_list int
  A(1  ).report();  // default b OVERRIDE default c initializer_list int
  A(1,2).report();  // default b default c OVERRIDE initializer_list int
}