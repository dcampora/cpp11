
#include <iostream>  // cout, endl
#include <algorithm> // for_each

using std::cout;
using std::endl;

int main() {
  int sum = 0;
  int product = 1;
  auto data = {1,2,3,4,5};

  std::for_each(begin(data), end(data),
    [&sum, &product](int datum) {
      sum += datum;
      product *= datum;
    });

  cout << "sum = "     << sum     << endl;
  cout << "product = " << product << endl;
}
