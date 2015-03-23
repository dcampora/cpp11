
#include <iostream>       // cout, endl
#include <thread>         // thread
#include <vector>         // vector
#include <mutex>
#include <string>

using std::cout; using std::endl;

int main() {
  int min = 100;
  int max = min + 20;
  std::vector<std::thread> threads;
  threads.reserve(max-min);

  std::packaged_task<std::string () > pckd_task(task);
  auto future = pckd_task.get_future(); // packaged_tasks have an associated future
  pckd_task();                          // packaged_tasks must be called to fulfil the promise of their futures
  std::cout << future.get() << std::endl;

  for (int n = min; n<max; ++n)
    threads.emplace_back([n, &m] {
        std::lock_guard<std::mutex> l {m};
        cout << n << " x " << n << " = " << n*n << endl;
    } );

  for (auto& t : threads)
    t.join();

}
