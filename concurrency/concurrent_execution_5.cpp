
#include <iostream> // cout, endl
#include <future>   // packaged_task

int task() { return 42; }

int main() {
  std::packaged_task<int()> pckd_task(task);
  auto future = pckd_task.get_future(); // packaged_tasks have an associated future
  pckd_task();                          // packaged_tasks must be called to fulfil the promise of their futures
  std::cout << future.get() << std::endl;
}
