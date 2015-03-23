#include <iostream> // cout, endl
#include <thread>   // this_thread
#include <future>   // async, future
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
  // async is implementation defined; it may / may not be concurrent
  auto                b = std::async(ask_the_brits);
  auto                f = std::async(ask_the_french);
  auto                g = std::async(ask_the_germans);
  auto                i = std::async(ask_the_italians);
  std::future<string> s = std::async(ask_the_spaniards);
  
  // Inspection of results
  // t->get can only be called once. It's a blocking call
  for (auto t: {&b,&f,&g,&i,&s})
    cout << t->get() << endl;
}
