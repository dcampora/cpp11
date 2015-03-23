
#include <iostream>   // cout, endl
#include <thread>     // thread

using std::cout; using std::endl;

void overload()      { cout << "void"        << endl; }
void overload(int i) { cout << "int = " << i << endl; }

int main() {
  
  // TODO! :)
  std::thread(/* overload( ) */).join();
  

  std::thread(/* overload(2) */).join();
}
