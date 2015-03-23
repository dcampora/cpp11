// Seq execution

#include <iostream> // cout, endl
#include <thread>   // this_thread
#include <chrono>   // chrono

using std::cout; using std::endl;

void connect() {
  // Get permission from the EU
  // Hire a translator
  // Establish the communications channel
  // This takes lots of time ...

// Hm...
#ifdef CPP14
  std::this_thread::sleep_for(std::chrono::seconds(2));
#else
  using namespace std::literals::chrono_literals;
  std::this_thread::sleep_for(2s);
#endif  
}

void call_the_brits()     { connect(); cout << "Let's go!"  << endl; }
void call_the_french()    { connect(); cout << "Allons-y!"  << endl; }
void call_the_germans()   { connect(); cout << "Gehen wir!" << endl; }
void call_the_italians()  { connect(); cout << "Andiamo!"   << endl; }
void call_the_spaniards() { connect(); cout << "¡Vamos!"    << endl; }

int main() {
  call_the_brits();
  call_the_french();
  call_the_germans();
  call_the_italians();
  call_the_spaniards();
}