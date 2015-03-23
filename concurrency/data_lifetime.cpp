
#include <iostream> // cout, endl
#include <thread>   // thread, this_thread
#include <chrono>   // chrono  
using std::cout; using std::endl;

const int CALL_HOME_TIMES = 100;

int count[] = {0,0,0,0,0,0};

struct Drone {
  Drone(int i) : i(i) {}
  int i;
  void call_home() { ++count[i]; } 
};

void doit(int i) {
  Drone d{i};
  std::thread{[&d] { // d is a reference to a temporary
      for (int x=0; x<CALL_HOME_TIMES; ++x)
        d.call_home();
    }
  }.detach();
}

int main() {
  for (auto x : {1,2,3,4,5})
    doit(x);
  std::this_thread::sleep_for(std::chrono::seconds(1));
  for (auto c: count)
    cout << c << endl;
}