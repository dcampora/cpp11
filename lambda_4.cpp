
#include <iostream>   // cout, endl
#include <vector>     // vector, begin, end
#include <algorithm>  // for_each, transform

// A guinea pig class that we will use in the exercises below.
struct Powers {
  Powers(int n_) : n(n_) {}
  int get_square() const { return n*n; }
  int get_cube()   const { return n*n*n; }
  int multiply_by(int m) const { return m*n; }

public:
  int n;
};

class PowerFactory {
public:
  Powers* operator()(int n){
    return new Powers(n);
  }
};

// Awesome functor to call relative functions that return int from
// the Powers class.
class GetSomething {
public:
  int (Powers::*fn)() const ;
  GetSomething(int (Powers::*fn_)() const) : fn(fn_) {}
  void operator()(Powers* p) const{
    // std::cout << std::hex << (void*) fn << std::dec << std::endl;
    std::cout << (p->*fn)() << " ";
  }
};

// Rewrite the following code without the use of lambdas.
int main() {
  std::vector<int> source({1,2,3,4,5});
  std::vector<Powers*> input(source.size(), nullptr);

  // transform(begin(source), end(source), begin(input),
  //           [](int n){ return new Powers(n);});
  // Hint: write a functor
  transform(begin(source), end(source), begin(input), PowerFactory());

  // for_each(begin(input), end(input), 
  //          [](Powers* p){ std::cout << p->get_square() << " ";});
  // Hint: use mem_fun, copy and ostream_iterator (or write a functor)
  for_each(begin(input), end(input), GetSomething(&Powers::get_square));
  std::cout << std::endl;


  // for_each(begin(input), end(input), 
  //          [](Powers* p){ std::cout << p->multiply_by(10) << " ";});
  // Hint: use bind, mem_fun, copy and ostream_iterator (or write a functor)
  // for_each(begin(input), end(input), 
  for_each(begin(input), end(input), GetSomething(&Powers::get_cube));

  for_each(begin(input), end(input), 
           [](Powers* p){ std::cout << p->get_square() + p->get_cube() << " ";});
  std::cout << std::endl;
  // Hint: Finding an inline expression to replace the lambda looks
  // very painful. A functor is your only realistic option.

  // BTW, did you spot our use of Koenig (argument dependent) lookup?
}
