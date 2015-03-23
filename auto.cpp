#include <map>    // map
#include <vector> // vector

namespace fruit {
  namespace banana {
    struct YellowSkinWithAFewBrownSplodges {};
  }
}

int main() {

  int a = 1;

  fruit::banana::YellowSkinWithAFewBrownSplodges* skin = new fruit::banana::YellowSkinWithAFewBrownSplodges;

  std::map<int, fruit::banana::YellowSkinWithAFewBrownSplodges> skin_map;
  for (auto it = begin(skin_map); it != end(skin_map); it++ ) {

  }
  for (auto it = begin(skin_map); it != end(skin_map); it++ ) {
    // TODO Do something with the pair
  }

  // Lots more to be done

  std::vector<int> v({1,2,3,4,5});
  for (auto& x : v)
    x++;

  // Instead of a template parameter

  // 
}
