#include <queue>              // queue
#include <deque>              // deque
#include <mutex>              // mutex, unique_lock, lock_guard
#include <condition_variable> // condition_variable

template<class T, class Container = std::deque<T>>
class concurrent_queue {
public:
  // Your implementation goes here
  // concurrent_queue() : queue(Container{}) {}
  concurrent_queue() = default;
  // ~concurrent_queue() = default;

  // push
  // void push(const T& t) {
  template<class Z> // perfect forwarding better requires universal... something (type deduction?)
  void push(Z&& t) {
    std::lock_guard<std::mutex> lock(m);
    c.notify_one();

    queue.push(t);
  }

  // pop_when_available
  T pop_when_available() {
    std::unique_lock<std::mutex> lock(m);
    c.wait(lock, [this]{ return queue.size() > 0; });
    const T t = queue.front();
    queue.pop();

    return t;
  }

private:
  // Your implementation goes here
  std::queue<T, Container> queue;
  mutable std::mutex m;
  mutable std::condition_variable c;
};

#include <iostream> // cout, endl;
#include <thread>   // thread, this_thread
#include <vector>   // vector
#include <chrono>   // chrono

////////////////////////////////////////////////////////////////////////////////

using std::cout; using std::endl;

int main() {

  concurrent_queue<int> queue;

  const int N_producers = 10;
  const int N_bursts    =  3;
  const int N_per_burst = 10;
  const int pause_in_s  =  2;

  // Spawned threads simultaneously fill the queue with data in bursts
  std::vector<std::thread> producers;
  producers.reserve(N_producers);

  for (int i=0; i<N_producers; ++i) {
    producers.emplace_back([pause_in_s, &queue] {

        for (int burst=0; burst<N_bursts; ++burst) {
          std::this_thread::sleep_for(std::chrono::seconds(pause_in_s));
          for (int n=0; n<N_per_burst; ++n) {
            queue.push(n);
          }
        }

      });
  }

  // Main thread takes data from the queue as soon as it's available
  int count = 0;
  while (count < N_producers * N_bursts * N_per_burst) {
    auto item = queue.pop_when_available();
    cout << item << std::flush;
    // cout.flush();
    ++count;
  }
  cout << endl;

  for (auto& t: producers)
    t.join();
}