#include <iostream>       // cout, endl
#include <future>         // async, future
#include <thread>         // thread, sleep_for
#include <vector>         // vector
#include <random>         // random_device, uniform_int_distribution
#include <chrono>         // chrono (system_clock, sleep_for)
#include <utility>        // declval

using std::cout; using std::endl;

//////////////////////////////////////////////////////////////////////////////////
// Some very important work that needs to be done.                              //
// Do not change the code in this box.                                          //
void work(int t) { std::this_thread::sleep_for(std::chrono::milliseconds(t)); } //
                                                                                //
int work_hard(int n) {                                                          //
  std::random_device rd;                                                        //
  std::uniform_int_distribution<int> choose(0, n);                              //
  int m = choose(rd);                                                           //
  work(m);                                                                      //
  return n - m;                                                                 //
}                                                                               //
                                                                                //
int step_1(int n) { return work_hard(n); }                                      //
int step_2(int n) { return work_hard(n); }                                      //
int step_3(int n) { return work_hard(n); }                                      //
int step_4(int n) { return work_hard(n); }                                      //
int step_5(int n) { return work_hard(n); }                                      //
int step_F(int n) {                                                             //
  // Ensure that all remaining work is done                                     //
  int m = n;                                                                    //
  work(m);                                                                      //
  return n - m;                                                                 //
}                                                                               //
//////////////////////////////////////////////////////////////////////////////////

template <typename Future, typename Continuation>
auto then(Future f, Continuation continue_) -> std::future<decltype(continue_(f.get()))> {
  return async(std::launch::async,
              // In C++1y, [f = std::move(f)] should work
               [continue_] (Future f) { return continue_(f.get()); }, 
               std::move(f) ); // Faking capture by move
}

int main() {

  int how_many = 10;
  auto job_size = 300;
  std::vector<int> jobs(how_many, job_size);
  auto start = std::chrono::system_clock::now();

  {
    std::vector<std::future<void>> fs;
    fs.reserve(how_many);
    for (auto job: jobs) {
      auto f1 = std::async(std::launch::async, step_1, job);
      auto f2 = then(std::move(f1), step_2);
      auto f3 = then(std::move(f2), step_3);
      auto f4 = then(std::move(f3), step_4);
      auto f5 = then(std::move(f4), step_5);
      auto fF = then(std::move(f5), step_F);
      fs.push_back(then(std::move(fF), [] (int r) { cout << "Remaining = " << r << endl; }));
    }
  }

  auto stop = std::chrono::system_clock::now();
  cout << "Completed in " 
       << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()/1000.0
       << "s\n";

}