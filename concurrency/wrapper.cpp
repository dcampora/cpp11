#include <iostream>       // cout, endl
#include <thread>         // thread
#include <mutex>          // mutex, lock_guard
#include <vector>         // vector

using std::cout; using std::endl;

// Your implementation of monitor goes here
template<typename T>
class monitor {
private:
  std::mutex _m;

public:
};


int main() {
  int min = 100;
  int max = min + 20;
  std::vector<std::thread> threads;
  threads.reserve(max-min);

  monitor<std::ostream&> exclusive_cout{cout}; // You have to implement monitor.

  for (int n = min; n<max; ++n)
    threads.emplace_back([/*Your capture spec goes here*/] {
        exclusive_cout([/*Your capture spec goes here*/] (std::ostream& cout) {
            cout << n << " x " << n << " = " << n*n << endl;
          });
      });

  for (auto& t : threads)
    t.join();

}
