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

  std::unique_lock<std::mutex> consumer_lock{mutex};

  auto worker_thread = std::thread([] (int n) {
      auto result = fib(n);
      std::cout << "I'm locked :(" << std::endl << std::flush;
      std::lock_guard<std::mutex> producer_lock(mutex);
      std::cout << "Hey! There we go! :D" << std::endl << std::flush;
      question = n;
      answer   = result;
      condition.notify_one();
    }, 43);

  condition.wait(consumer_lock, [] { return answer > 0; });
  consumer_lock.unlock();

  cout << "The result is: fib(" << question << ") = " << answer << endl;
  worker_thread.join();
}