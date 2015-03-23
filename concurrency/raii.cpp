#include <iostream>  // cout, endl
#include <thread>    // thread
#include <random>    // random_device, uniform_int_distribution
#include <stdexcept> // runtime_error

using std::cout; using std::endl;

void do_something_else() {
  std::random_device rd;
  std::uniform_int_distribution<int> true_or_false(0, 1);
  if (true_or_false(rd)) 
    cout << "Nothing to see here, move along now." << endl;
  else {
    cout << "Something exceptional is happening ..." << endl;
    throw(std::runtime_error("Very exceptional indeed"));
  }
}

void intermediate_level() {
  // t gets destructed when we go out of scope,
  // so we could put the join in the destructor

  // RAII takes care of initializing / destructing for you.
  // Dynamically allocated stuff doesn't do this.
  // Q: Can this be achieved?
  std::thread t([] { cout << "Strut your stuff: "; });
  do_something_else();
  t.join();
}

int main() {
  for (int i=0; i<10; ++i)
    try {
      intermediate_level();
    } catch (...) {
      cout << "                  ... Dealing with it" << endl;
    }
}
