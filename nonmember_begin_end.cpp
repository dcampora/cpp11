
#include <iostream>  // cout, endl
#include <vector>    // vector, begin, end
#include <algorithm> // for_each

// #include <stdlib.h>

using std::begin;
using std::end;
using std::for_each;
using std::cout;
using std::endl;

void doit(int i) { cout << i << " "; } // Something to be used by for_each

void foo(int a[10]); // Ignore this until we see its definition

int main() {

  int a[] = {1,2,3,4,5};
  for_each(begin(a), end(a), doit); // nonmember begin and end work on arrays
  cout << endl;

  // Will not work, since we don't know the size of b
  // int *b = (int*) malloc(5 * sizeof(int));
  // for_each(begin(b), end(b), doit);
  // cout << endl;

  std::vector<int> v(begin(a), end(a));
  for_each(begin(v), end(v), doit); // exactly the same pattern works on STL-like containers
  cout << endl;

  // The concept of 'end of pointer' doesn't exist
  int* p = a;
  //for_each(begin(p), end(p), doit); // Error: pointer has no end
  cout << endl;

  // foo(a); // Error: passing arrays loses length information

}

// void foo(int a[10]) {
//   for_each(begin(a), end(a), doit); // Error: passing arrays loses length information
//   cout << endl;
// }
