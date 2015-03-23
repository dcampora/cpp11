#include <iostream>           // cout, endl
#include <condition_variable> // conditon_variable
#include <mutex>              // mutex, unique_lock, lock_guard
#include <thread>             // thread

using std::cout; using std::endl;

std::mutex mutex;
std::condition_variable condition;

int question = -1;
int answer = -1;

int fib(int n) { return n<2 ? 1 : fib(n-1) + fib(n-2); }

int main() {

  auto worker_thread = std::thread([] (int n) {
      auto result = fib(n);
      std::lock_guard<std::mutex> producer_lock(mutex);
      question = n;
      answer   = result;
      condition.notify_one();
    }, 43);

  // {
    std::unique_lock<std::mutex> consumer_lock{mutex};
    cout << "Calling thread going to sleep until result is available." << endl;
    cout << "First condition check happens immediately ..." << endl;

    // consumer_lock is released by wait ...
    condition.wait(consumer_lock, [] { 
        // The wait predicate is executed:

        //   1. as soon as wait is called,
        //   2. in response to condition.notify_one() or
        //      condition.notify().

        // The first time the predicate returns true, wait returns and
        // the waiting thread is woken up.
        cout << "Wait predicate checking whether this thread should be woken up (" 
             << answer << " > 0)." << endl;
        if (answer > 0) {
          cout << "    Yes, the result has arrived so let's wake up." << endl;
          return true;
        } else {
          cout << "    No, the result is not there yet, so let this thread sleep on." << endl;
          cout << "    Will check again when notified." << endl;
          return false;
        }});
    // consumer_lock is locked again when wait returns.
    cout << "Calling thread wakes: wait returned." << endl;
  // } // RAII: consumer_lock.unlock()

  cout << "The result is: fib(" << question << ") = " << answer << endl;
  worker_thread.join(); // Destructor will crash unless joined or detached.
}