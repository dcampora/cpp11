#include <iostream>       // cout, endl
#include <thread>         // thread
#include <vector>         // vector
#include <algorithm>      // accumulate
#include <random>         // random_device, uniform_int_distribution
#include <mutex>          // mutex, lock_guard

using std::cout; using std::endl;

struct Foo {
  int n;
  std::mutex mutex; // Not copyable, so you will need to write a copy constructor
  Foo(int n) : n(n)  {}
  Foo(const Foo& other) : n(other.n), mutex() {} // Each copy gets its own new mutex
  friend void transfer(Foo& source, Foo& target) { 
    source.n--;
    target.n++;
  }
};

void report (std::vector<Foo>& foos) {
  for (auto& f : foos)
    cout << f.n << " ";
  cout << " ->  ";
  cout << accumulate(begin(foos), end(foos), 0, 
                     [] (int running_total, const Foo& f) { return f.n + running_total; })
       << endl;
}

const int N_threads = 8;
const int transfers_per_thread = 1000;
const int N_foos = 5;

int main() {

  std::vector<Foo> foos;
  foos.reserve(N_foos);
  for (int n=0; n<N_foos; ++n)
    foos.emplace_back(0);
  report(foos);

  std::vector<std::thread> threads;
  threads.reserve(N_threads);
  for (int n=0; n<N_threads; n++)
    threads.emplace_back([&foos] {
        std::random_device rd;
        std::uniform_int_distribution<int> choose(0, foos.size()-1);
        for (int s=0; s<transfers_per_thread; ++s) {

          // Pick two different Foos
          int left_index  = choose(rd);
          int right_index = left_index;
          while (left_index == right_index) {
            right_index = choose(rd);
          }
          Foo& l = foos[left_index];
          Foo& r = foos[right_index];

          // Attempting to use mutexes to protect shared data, but getting deadlock.
          std::lock_guard<std::mutex> guard_l(l.mutex);
          std::lock_guard<std::mutex> guard_r(r.mutex);

          transfer(l, r);
        }
      });

  for (auto& t : threads)
    t.join();

  report(foos);
}