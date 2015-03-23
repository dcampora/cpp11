
#include <iostream> // cout, endl
#include <cstddef>  // size_t
#include <utility>  // move


using std::cout; using std::endl; using std::size_t;

typedef int T;


// Movable(const Movable&  o) { cout << "M: Copy constructing " << o.n << endl; }
// Movable(      Movable&& o) { cout << "M: Move constructing " << o.n << endl; }
// void operator=(const Movable&  o) { cout << "M: Copy assigning    " << o.n << endl; }
// void operator=(      Movable&& o) { cout << "M: Move assigning    " << o.n << endl; }

class Vectorish {
public:
  Vectorish(size_t N, int start=0) : data(nullptr), size(N) {
    if (N>0) {
      data = ALLOCATE(N);
      for (size_t i=0; i<N; ++i)
        data[i] = start+i;
    }
  }


// class Foo {
//     Foo(Foo&& other) : Foo() {
//       swap(*this, other);
//     }
// };
  Vectorish(const Vectorish& other) : data(ALLOCATE(other.size)), size(other.size) {
    COPY(other);
    // swap(*this, other);
  }


  Vectorish(Vectorish&& other) : data(nullptr), size(0) {
    SWAP(other);
  }

  // In order to get the copy (Vectorish other),
  // either the Vectorish(const Vectorish& other) or Vectorish(Vectorish&& other)
  // constructor is called upon receiving the thing by value. (cool!)

  // So when doing the assignment operator with only passing by value,
  // this is done automatically! (and it's precisely what we need).
  Vectorish& operator=(Vectorish other) { // by value! we want to move
    swap(*this, other);
    return *this;
  }

  // Vectorish& operator=(Vectorish&& other) {
  //   SWAP(other);
  //   return *this;
  // }

  T& operator[](size_t n) { return data[n]; }

  ~Vectorish() { RELEASE(); }

private:
  T* data;
  std::size_t size;

  // This is used twice. In the solution it is only used once, so
  // inline it there.
  void COPY(const Vectorish& other) {
    cout << "Copying      " << size << " elements" << endl;
    for (size_t i=0; i<size; ++i) {
      data[i] = other.data[i];
    }
  }

  // Used 3 times. In the solution it should only be used twice.
  T* ALLOCATE(size_t N) {
    cout << "Allocating   " << N << " elements" << endl;
    return new T[N];
  }

  // Used twice. In the solution it is only used once, so inline it
  // there.
  void RELEASE() {
    cout << "Deallocating " << size << " elements" << endl;
    delete [] data;
  }

  // Move this out of the class to overload the generic swap operation
  void SWAP(Vectorish& other) {
    using std::swap;
    swap(data, other.data);
    swap(size, other.size);
  }
};


int main() {
  cout << "---------- Construction: should allocate 10000 ----------" << endl;
  Vectorish* v = new Vectorish(10000);
  cout << "---------- Destruction: should deallocate 10000 ----------" << endl;
  delete v;
  cout << "---------- done ----------" << endl;
  // Use dynamically allocated objects to keep precise control over
  // destruction times.
  Vectorish* source1 = new Vectorish(100);
  Vectorish* source2 = new Vectorish(200);
  Vectorish* source3 = new Vectorish(300);
  cout << "---------- Copy construction should allocate 100, copy 100 ----------" << endl;
  Vectorish* target1 = new Vectorish(*source1);
  cout << "---------- Move construction should NOT allocate, copy or deallocate ...  ----------" << endl;
  Vectorish* target2 = new Vectorish(std::move(*source2));
  cout << "---------- ... but source2 destructor should deallocate 0 ----------" << endl;
  delete source2;
  cout << "---------- Copy assignment should allocate 100 copy 100 deallocate 200  ----------" << endl;
  *target2 = *source1;
  cout << "---------- Move assignment and source3 destructor should deallocate 100 between them  ----------" << endl;
  *target2 = std::move(*source3);
  delete source3;
  cout << "---------- target1 destructor should deallocate 100 ----------" << endl;
  delete target1;
  cout << "---------- target2 destructor should deallocate 300 ----------" << endl;
  delete target2;
  cout << "---------- source1 destructor should deallocate 100 ----------" << endl;
  delete source1;
  cout << "---------- done ----------" << endl;

}