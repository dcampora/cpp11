
#include <iostream>   // cout, endl
#include <functional>

using std::cout; using std::endl;
enum class Fuzzy { Yes, Maybe, No };

void fuzzy_if(Fuzzy condition, std::function<void()> f1,
    std::function<void()> f2, std::function<void()> f3){
    switch (condition){
        case Fuzzy::Yes:
            f1();
            break;
        case Fuzzy::Maybe:
            f2();
            break;
        case Fuzzy::No:
            f3();
            break;
    }
}

Fuzzy is_big(int n) {
  if (n<10)  return Fuzzy::No;
  if (n>100) return Fuzzy::Yes;
  return Fuzzy::Maybe;
}

int main() {
  for (auto n: {2,7, 30, 50, 200, 1000}) {
    fuzzy_if(is_big(n),
        [=]{ cout << n << " is big" << endl; },
        [=]{ cout << "not sure whether " << n << " is big" << endl; },
        [=]{ cout << n << " is definitely not big" << endl; });
    // fuzzy_if(is_big(n)) { cout << n << " is big" << endl; }
    // else                { cout << n << " is definitely not big" << endl; }
    // maybe               { cout << "not sure whether " << n << " is big" << endl;}
  }
}
