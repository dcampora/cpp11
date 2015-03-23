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

  // Store the packaged tasks in a container
  std::vector<std::packaged_task<string()>> tasks;
  tasks.reserve(5);
  for(const auto& fn : {ask_the_brits, 
                        ask_the_french, 
                        ask_the_germans,
                        ask_the_italians,
                        ask_the_spaniards})
    tasks.emplace_back(fn);

  // A container of the futures attached to the packaged tasks
  std::vector<std::future<string>> futures;
  futures.reserve(5);
  for(auto& task : tasks)
    futures.push_back(task.get_future());

  // A container of threads on which the tasks will be executed
  std::vector<std::thread> threads;
  threads.reserve(5);
  for(auto& task : tasks)
    // task is an L-Value, so we need to move
    // It's like calling the thread constructor
    threads.emplace_back(std::move(task));

  // Wait for all threads to complete
  for(auto& thread : threads)
    thread.join(); // Needed for the program not to crash

  // Display all the results
  for(auto& future : futures)
    cout << future.get() << endl;

}