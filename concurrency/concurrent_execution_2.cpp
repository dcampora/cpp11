
#include <iostream> // cout, endl
#include <thread>   // thread, this_thread
#include <chrono>   // chrono

using std::cout; using std::endl;

void connect() {
  // Get permission from the EU
  // Hire a translator
  // Establish the communications channel
  // This takes lots of time ...
  std::this_thread::sleep_for(std::chrono::seconds(2));
}

void call_the_brits()     { connect(); cout << "Let's go!"  << endl; }
void call_the_french()    { connect(); cout << "Allons-y!"  << endl; }
void call_the_germans()   { connect(); cout << "Gehen wir!" << endl; }
void call_the_italians()  { connect(); cout << "Andiamo!"   << endl; }
void call_the_spaniards() { connect(); cout << "¡Vamos!"    << endl; }

int main() {
  std::thread b(call_the_brits);
  std::thread f(call_the_french);
  std::thread g(call_the_germans);
  std::thread i(call_the_italians);
  std::thread s(call_the_spaniards);
  
  // for (auto t: {b,f,g,i,s}) // This would be wrong, as it would try to copy
  
  // Commenting out the join would guarantee a crash, as it requires explicit join / detach
  for (auto t: {&b,&f,&g,&i,&s})
    t->join(); // Will block until thread t is finished
}
