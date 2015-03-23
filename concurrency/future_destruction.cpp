#include <iostream> // cout, endl
#include <thread>   // sleep_for
#include <future>   // async
#include <chrono>   // chrono

using std::cout; using std::endl; using std::async;

void sleep(int t) { std::this_thread::sleep_for(std::chrono::seconds(t)); }

int main() {

  auto policy = std::launch::async;
  auto duration = 1;

  cout << "Starting block 1" << endl;
  // future calls join automagically in the destructor.
  // Things are defined in a different context ({}),
  // so they will destruct after the context
  {
    // however, in this case, these are temporaries, so
    // destructors are called right away
    async(policy, sleep, duration);   // future a
    // destructor temporary a -> join -> wait

    async(policy, sleep, duration);   // future b
    // destructor temporary b -> join -> wait

    async(policy, sleep, duration);   // future c
    async(policy, sleep, duration);   // future d
    // ...
  }
  cout << "Starting block 2" << endl;
  {
    auto e = async(policy, sleep, duration);
    auto f = async(policy, sleep, duration);
    auto g = async(policy, sleep, duration);
    auto h = async(policy, sleep, duration);

    // destructor of e, f, g and h, in order; only they are executing
    // concurrently, so 1 second in total
  }
  cout << "Done" << endl;
}