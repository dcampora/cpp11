
#include <iostream> // cout, endl
#include <memory>   // shared_ptr, make_shared
#include <utility>  // move


using std::cout; using std::endl;
using std::shared_ptr; using std::make_shared;

class Foo {
public:
  Foo(int n)         : n{n}   { cout << "construct " << n << endl; }
  Foo(const Foo&  o) : n{o.n} { cout << "copy      " << n << endl; }
  Foo(      Foo&& o) : n{o.n} { cout << "move      " << n << endl; }
  ~Foo()                      { cout << "destroy   " << n << endl; }
  void id() { cout << n << endl; }
private:
  int n;
};

void take_shared_by_value(std::shared_ptr<Foo> f) { 
  cout << " --> " << endl << "     ";
  f->id(); 
  cout << " <-- " << endl;
}

void take_shared_by_reference(const std::shared_ptr<Foo>& f) { 
  cout << " --> " << endl << "     ";
  f->id(); 
  cout << " <-- " << endl;
}

void report(const shared_ptr<Foo>& f) {
  cout << "*" << f.get() << " = "; cout.flush();
}

int main() {

  {
    auto f1 = std::make_shared<Foo>(1);
    auto f2 = std::make_shared<Foo>(2);

    report(f1); f1->id();
    report(f2); f2->id();

    // dcampora: f1 is destroyed
    f1 = f2;

    report(f1); f1->id();
    report(f2); f2->id();
  }
  cout << "-----------------" << endl;
  {
    auto f1 = std::make_shared<Foo>(1);
    auto f2 = std::make_shared<Foo>(2);

    report(f1); f1->id();
    report(f2); f2->id();

    // dcampora: f2 is deleted (prepared for deletion, because of moving)
    f1 = std::move(f2);

    report(f1); f1->id();
    report(f2); //f2->id(); // Bang!
  }
  cout << "-----------------" << endl;
  { 
    auto f = std::make_shared<Foo>(2);

    take_shared_by_value(f);
    report(f); f->id();

    // dcampora: std::move is not doing anything here. 
    // take_shared_by_reference takes a reference (F&),
    // so it "falls back" to that overloaded function definition.
    take_shared_by_reference(std::move(f));
    report(f); f->id();

    take_shared_by_value(std::move(f));
    report(f); //f->id(); // Bang!
  }
}
