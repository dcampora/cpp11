
#include <iostream>  // cout, endl
#include <cstddef>   // size_t
// #include <initializer_list>

using std::cout; using std::endl; using std::size_t;

typedef int T;

class Vec {
public:
  // Implement constructor
  Vec(std::initializer_list<T> values) :
    size(values.size()) {

    data = new T[size];
    for (int i=0; i<size; ++i)
      data[i] = values[i];
  }

  // Implement append
  void append(std::initializer_list<T> values) {
    // We have to make data bigger.
    T* prev_data = data;

    // New data
    size += values.size();
    data = new T[size];
    for (int i=0; i<size; ++i)
      data[i] = values[i];

    delete prev_data;
  }

  void show() {
    cout << "[";
    for(size_t i=0; i<size-1; ++i) {
      cout << data[i] << ", ";
    }
    cout << data[size-1] << "]" << endl;
  }
private:
  T* data;
  size_t size;
};

int main() {
  Vec v{1,2,3,4};
  v.show();

  Vec w = {5,6,7};
  w.show();

  Vec{8,9}.show();

  Vec* p = new Vec {10,11,12};
  p->show();

  v.append({3,2,1});
  v.show();
}