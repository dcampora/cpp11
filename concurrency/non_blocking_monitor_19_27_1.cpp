
#include <iostream>       // cout, endl
#include <thread>         // thread
#include <vector>         // vector
#include <queue>              // queue
#include <deque>              // deque
#include <mutex>              // mutex, unique_lock, lock_guard
#include <condition_variable> // condition_variable

using std::cout; using std::endl; using std::ostream;

// Concurrent queue
template<class T, class Container = std::deque<T>>
class concurrent_queue {
public:
  // Your implementation goes here
  // concurrent_queue() : queue(Container{}) {}
  concurrent_queue() = default;
  ~concurrent_queue() = default;

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

// T& doesn't work, for some reason I don't get.
// error: template argument for non-type template parameter must be an expression
// template<class T&>

// I don't like it, but T seems to match (?)
template<class T>
class active {
private:
  std::thread worker_thread;
  T& wrapped_object;

public:
  // perfect forwarding
  template<class Z>
  active(Z&& z) : wrapped_object(z) {}

  // perfect forwarding
  template<class Action>
  void operator()(Action&& a){
    a(wrapped_object);

    // Next step would be to use the queue we defined
    // on top, and execute it whenever things come and
    // are available.
  }
};


int main() {
  int min = 100;
  int max = min + 20;
  std::vector<std::thread> threads;
  threads.reserve(max-min);

  // A non-blocking thread-safe version of cout
  active<ostream&> syncout {cout};

  for (int n = min; n<max; ++n)
    threads.emplace_back([&n,&syncout] {

        syncout([n](ostream& cout) { cout << n << " x " << n << " = " << n*n << endl; });

      });

  for (auto& t : threads)
    t.join();
}
