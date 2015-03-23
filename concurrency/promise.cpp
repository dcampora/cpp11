
#include <iostream>  // cout, endl
#include <future>    // promise
#include <exception> // copy_exception
#include <stdexcept> // runtime_error
using std::cout; using std::endl;

int main() {

  // Fulfilling a promise

  std::promise<int> promise;          // A promise to provide an int
  auto future = promise.get_future(); // The means of accessing the promised int
  promise.set_value(42);              // Fulfil the promise (typically in some other thread)
  cout << future.get() << endl;       // Get the promised value

  // promise.set_value(666);          // Error, cannot satisfy a single promise more than once


  // Exception-raising promises

  std::promise<int> p;
  auto f = p.get_future();
  // Setting exception rather than value
  p.set_exception(std::copy_exception(std::runtime_error("Ooops")));
  // The future's get() will now throw that exception that was set
  // above
  try {
    cout << f.get() << endl;
  } catch (std::exception& e) {
    cout << e.what() << endl;
  }
}