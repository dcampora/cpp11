
#include <iostream> // cout, endl
#include <thread>   // this_thread
#include <future>   // async
#include <chrono>   // chrono

using std::cout; using std::endl; using std::string;

void connect() {
  // Get permission from the EU
  // Hire a translator
  // Establish the communications channel
  // This takes lots of time ...
  std::this_thread::sleep_for(std::chrono::seconds(2));
}

string ask_the_brits()     { connect(); return "OK"        ; }
string ask_the_french()    { connect(); return "D'accord"  ; }
string ask_the_germans()   { connect(); return "In Ordnung"; }
string ask_the_italians()  { connect(); return "Va bene"   ; }
string ask_the_spaniards() { connect(); return "Vale"      ; }

int main() {
  // Task specification
  // There are three call policies:
  //  async    - concurrent
  //  deferred - lazy evalutaion, at "get"
  //  any      - compiler chooses the one that's best
  auto b = std::async(std::launch::async, ask_the_brits);
  auto f = std::async(std::launch::async, ask_the_french);
  auto g = std::async(std::launch::async, ask_the_germans);
  auto i = std::async(std::launch::async, ask_the_italians);
  auto s = std::async(std::launch::async, ask_the_spaniards);
  
  // Inspection of results
  for (auto t: {&b,&f,&g,&i,&s})
    cout << t->get() << endl;
}
