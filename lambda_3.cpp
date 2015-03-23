
#include <iostream>   // cout, endl
#include <vector>     // vector

using std::cout; using std::endl;

template<class CONTAINER, class GENERATE, class FINISHED>
void expand(CONTAINER& c, GENERATE generate, FINISHED finished) {
  while (!finished())
    c.push_back(generate());
}

int main() {
  std::vector<int> v{1,2,3};
  expand(v,
        [&]{
            return v[v.size()-3];
        },
        [&]{
            return v.size()==20;
        });

  for (auto& e: v) 
    cout << e << " "; // 1 2 3 1 2 3 1 2 3 1 2 3 1 2 3 1 2 3 1 2 
  cout << endl;
}
