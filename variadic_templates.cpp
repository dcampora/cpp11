
#include <iostream> // cout, endl
#include <utility>  // forward


using std::cout; using std::endl;

template<class T>
class Vectorish {
public:

  Vectorish(size_t N) 
    : data{static_cast<T*>(operator new(sizeof(T)*N))},
      size{0},
      reserved{N}
  {}

  T& operator [] (size_t N) { return data[N]; }

  // Generalize this function, making sure that it supports perfect
  // forwarding.
  template<class... TemplateParameterPack>
  void emplace_back(TemplateParameterPack&&... FunctionParameterPack) {

    new (data+size) T{std::forward<TemplateParameterPack>(FunctionParameterPack)...};
    ++size;

    // new (data+size) T{FunctionParameterPack...};
    // ++size;

    // data[size] = int{i};
  }


private:
  T* data;
  size_t size;
  size_t reserved;
};

struct Foo {
  Foo(int n)         : n{n}   { cout << "construct " << n << endl; }
  Foo(const Foo&  o) : n{o.n} { cout << "copy Foo "  << n << endl; }
  Foo(      Foo&& o) : n{o.n} { cout << "move Foo "  << n << endl; }
  int n;
};

struct Bar {
  // A perfectly forwarding constructor
  template<class F1, class F2>
  Bar(F1&& f1, F2&& f2) : f1(std::forward<F1>(f1)), f2(std::forward<F2>(f2)) {
    cout << "Constructing Bar " << f1.n << " " << f2.n << endl;
  }

  Foo f1, f2;
};

int main() {

  Vectorish<int> vi{10};
  vi.emplace_back(178);
  cout << vi[0] << endl;

  // make Vectorish<>::emplace_back work with the following client
  // code.

  Foo f1{1};
  Foo f2{2};
  Foo f3{3};
  Foo f4{4};

  Vectorish<Bar> vb{10};

  cout << "------- Should copy 1, move 2 -------" << endl;
  vb.emplace_back(f1, std::move(f2));

  cout << "------- Should move 3, copy 4 -------" << endl;
  vb.emplace_back(std::move(f3), f4);

}
