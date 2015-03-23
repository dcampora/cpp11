
#include <iostream> // cout, endl
#include <thread>   // this_thread
#include <future>   // packaged_task
#include <chrono>   // chrono
#include <vector>   // vector

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


  // std::packaged_task<int()> pckd_task(task);
  // auto future = pckd_task.get_future(); // packaged_tasks have an associated future
  // pckd_task();                          // packaged_tasks must be called to fulfil the promise of their futures
  // std::cout << future.get() << std::endl;


  // Store the packaged tasks in a container
  // Your code goes here ...
  // Note: decltype(ask_the_brits)
  std::vector<std::packaged_task<string()>> tasks;
  tasks.reserve(5);
  // Move all inside
  // DOing...
  for(const auto& tn){
    ask_the_brits,
    ask_the_french,
    ask_the_germans,
    ask_the_italians,
    ask_the_spaniards
  };

  // Store the futures attached to the packaged tasks in a container
  // Your code goes here ...

  // Store the threads on which the tasks will be executed, in a container
  // Your code goes here ...

  // Wait for all threads to complete
  // Your code goes here ...

  // Display all the results
  // Your code goes here ...
}
