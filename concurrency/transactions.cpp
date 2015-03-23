#include <iostream>       // cout, endl
#include <thread>         // thread
#include <vector>         // vector
#include <random>         // random_device, uniform_int_distribution
#include <mutex>          // mutex, lock_guard

using std::cout; using std::endl;

struct Foo {
  // Class invariant: sum = a + b 
  int a, b, sum;

  mutable std::mutex mutex;

  Foo(int a, int b) : a{a}, b{b}, sum{a+b}  {}

  // Locks the copy constructor
  Foo(const Foo& other, const std::lock_guard<std::mutex>&) : a{other.a}, b{other.b}, sum{other.sum}, mutex{} {}
  Foo(const Foo& other) : Foo(other, std::lock_guard<std::mutex>(other.mutex)) {} // Lock and delegate

  void bump() {
    std::lock_guard<std::mutex> l{mutex};
    a += 1;
    b -= 1;
    if (b<0) {
      b += 10;
      a -= 10;
    }
  }

  bool check_invariant() const {
    std::lock_guard<std::mutex> l{mutex}; // TODO: why does it work without this?
    if (a+b != sum) {
      cout << "Problem: " << a << " + " << b << " = " << sum << endl;
      return false;
    }
    return true;
  }
};

const int N_threads = 8;
const int jobs_per_thread = 1000;
const int N_foos = 5;

int main() {

  std::random_device rd;
  std::uniform_int_distribution<int> choose(1, 5);

  std::vector<Foo> foos;
  foos.reserve(N_foos);
  for (int n=0; n<N_foos; ++n)
    foos.emplace_back(choose(rd), choose(rd));

  std::vector<std::thread> threads;
  threads.reserve(N_threads);
  for (int n=0; n<N_threads; n++)
    threads.emplace_back([&foos] {
        std::random_device rd;
        std::uniform_int_distribution<int> choose(0, foos.size()-1);
        for (int s=0; s<jobs_per_thread; ++s) {
          Foo& f = foos[choose(rd)];
          f.bump();
          Foo g{f};
          g.check_invariant();
        }
      });

  for (auto& t : threads)
    t.join();

}