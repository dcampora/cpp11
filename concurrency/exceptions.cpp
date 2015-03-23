// Use the concurrent queue we made earlier

#include <queue>              // queue
#include <deque>              // deque
#include <mutex>              // mutex, unique_lock, lock_guard
#include <condition_variable> // condition_variable

template<class T, class Container = std::deque<T>>
  class concurrent_queue {
  public:
    concurrent_queue() = default;
    void push(T item) {
      std::lock_guard<std::mutex> lock{mutex};
      queue.push(item);
      condition.notify_one();
    }

    T pop_when_available() {
      std::unique_lock<std::mutex> lock{mutex};
      condition.wait(lock, [this] { return queue.size() > 0; });
      T item = std::move(queue.front());
      queue.pop();
      lock.unlock();
      return item;
    }
  private:
    std::mutex               mutex;
    std::queue<T, Container> queue;
    std::condition_variable  condition;
  };

////////////////////////////////////////////////////////////////////////////////

// Use the wrapper pattern to add a message queue with a worker thread
// to the wrapped object.

#include <iostream>           // cout, endl
#include <thread>             // thread
#include <future>             // future, promise
#include <functional>         // function
#include <memory>             // make_shared
#include <exception>          // current_exception

/////////////////////////////////////////////////////////////////////////////////
// Helpers: allow both void and non-void promise.set_value() to be set         //
// identically.                                                                //
template<class R, class A, class T>                                            //
void set_value(std::promise<R   >& p, A& a, T& t) {       p.set_value(a(t)); } //
//
template<         class A, class T>                                            //
void set_value(std::promise<void>& p, A& a, T& t) { a(t); p.set_value(    ); } //
/////////////////////////////////////////////////////////////////////////////////

template<class T>
class active {
private:
  T target;
  mutable concurrent_queue<std::function<void(void)>> action_queue;
  bool done = false;
  std::thread worker_thread;
public:
  active(T target = T{}) :
    target(target),
    worker_thread([this] {
        while (!done)
          action_queue.pop_when_available()();
      })
  {}

  ~active() {
    action_queue.push([this] { done = true; });
    worker_thread.join();
  }

  template<class Action>
  auto operator()(Action action) const -> std::future<decltype(action(target))> {
    auto promise = std::make_shared<std::promise<     decltype(action(target))>> ();
    action_queue.push([this, promise, action] {
        try         { set_value(*promise, action, target); }
        catch (...) { promise->set_exception(std::current_exception()); }
      });
    return promise->get_future();
  }
};

// Run some actions purely for their side effect, others for their
// result, while some may throw an exception which future.get() must
// propagate.

#include <iostream>       // cout, endl
#include <thread>         // thread
#include <vector>         // vector

using std::cout; using std::endl; using std::ostream;

int main() {
  int min = 100;
  int max = min + 20;
  std::vector<std::thread> threads;
  threads.reserve(max-min);

  int total = 0;
  active<int&> synctotal{total};
  active<ostream&> syncout{cout};

  for (unsigned n = min; n<max; ++n)
    threads.emplace_back([n, &syncout, &synctotal] {
        std::shared_future<int> f = synctotal([n] (int& total) { 
            if (n%2)
              throw std::runtime_error("Don't like odd numbers");
            total += n;
            return total;
          });
        syncout([f](ostream& cout) {
            try {
              cout << "total = " << f.get() << endl; 
            } catch(...) {
              cout << "            how odd" << endl;
            }
          });
      });

  for (auto& t : threads)
    t.join();
}