#include <iostream>       // cout, endl
#include <thread>         // thread
#include <vector>         // vector
#include <mutex>

using std::cout; using std::endl;

int main() {
  int min = 100;
  int max = min + 20;
  std::vector<std::thread> threads;
  threads.reserve(max-min);

  std::mutex m;

  for (int n = min; n<max; ++n)
    threads.emplace_back([n, &m] {
        std::lock_guard<std::mutex> l {m};
        cout << n << " x " << n << " = " << n*n << endl;
    } );

  for (auto& t : threads)
    t.join();

}
