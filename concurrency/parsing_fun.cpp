
#include <iostream> // cout, endl
#include <thread>   // thread, this_thread

using std::cout; using std::endl;

struct Functor {
  Functor()          { cout << "Constructing the functor" << endl; }
  void operator() () { cout << "Running the functor"      << endl; }
};

int main() {
  std::thread t(Functor());
  t.join();
}