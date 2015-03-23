
#include <iostream> // cout, endl
#include <utility> // move

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


template<class T>
T make(int n) { 
  T new_one(n);
  return new_one;
}

template<class T>
void test() {
  T target(0);
  T a(1);
  target = a;                   // 1. Copy assign
  target = T(2);                // 2. Move assign
  target = make<T>(3);          // 3. Move assign
  target = std::move(a);        // 4. Move assign - Now it's in a "destructible" state.
  target = static_cast<T&&>(a); // 5. Move assign -
                                //    C++ compilers don't bother, but this should actually be a warning.
}

void accept_rvalue(Movable&& r) {
  Movable target = r;           // 6. Copy construct
}

int main() {
  test<Movable>();
  cout << "=================================" << endl;
  test<Immovable>();
  cout << "=================================" << endl;
  accept_rvalue(6);
}
