#include <iostream> // cout, endl

using std::cout;
using std::endl;

// A class which is both copyable and movable
struct Movable {
         Movable(int n_): n(n_)     {}
         Movable(const Movable&  o) { cout << "M: Copy constructing " << o.n << endl; }
         Movable(      Movable&& o) { cout << "M: Move constructing " << o.n << endl; }
  void operator=(const Movable&  o) { cout << "M: Copy assigning    " << o.n << endl; }
  void operator=(      Movable&& o) { cout << "M: Move assigning    " << o.n << endl; }
private:
  int n;
};

// A class which is copyable but not movable
struct Immovable {
       Immovable(int n_): n(n_)      {}
       Immovable(const Immovable& o) { cout << "I: Copy constructing " << o.n << endl; }
  void operator=(const Immovable& o) { cout << "I: Copy assigning    " << o.n << endl; }
private:
  int n;
};