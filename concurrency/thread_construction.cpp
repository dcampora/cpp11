#include <iostream>   // cout, endl
#include <thread>     // thread

using std::cout; using std::endl;

void function(int& i) {  ++i; }

int main() {
  int i = 1;
  
  // Error
  // std::thread(function, i).join();

  // First solution (std::ref)
  std::thread(function, std::ref(i)).join();

  // Lambda, easier!
  // First arg is duck type callable! :)
  std::thread([&i] {++i;}).join();

  cout << i << endl;
}
