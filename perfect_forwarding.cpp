
#include <utility> // move
#include "movable.cc"

class Base {
public:
  // Base(const Movable& m_) : m(m_) {}
  // Base(Movable&& m_) : m(std::move(m_)) {}

  // Base(const Movable& m, const Movable& n) : 
  //   m(m), n(n) {}
  // Base(Movable&& m, Movable&& n) : 
  //   m(std::move(m)), n(std::move(n)) {}

  // Base(const Movable& m, Movable&& n) : 
  //   m() ... // by 4

    // Cooler solution (using std::foward)
    // template<class T>
    // Base(T&& m) : m(std::forward<T>(m)) {}

    template<class T, class Z>
    Base(T&& m, Z&& n)  {}

    

private:
  // Movable m;
  // Movable n;
};

int main() {
    Movable m3(3), m4(4), m5(5), m8(8);

    A a;

  // Movable m2(2), m3(3);
  // Base b1(Movable(1));    // Should move 1
  // Base b2(m2);            // Should copy 2
  // Base b3(std::move(m3)); // Should move 3
  
    Base b1(Movable(1), Movable(2)); // Should move 1 & 2
    Base b2(a, a);                 // Should copy 3 & 4
    Base b3(m5, Movable(6));         // Should copy 5, move 6
    Base b4(Movable(7), m8);         // Should move 7, copy 8

    return 0;
}
