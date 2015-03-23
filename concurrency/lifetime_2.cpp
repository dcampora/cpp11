
#include <iostream> // cout, endl
#include <thread>   // thread

using std::cout; using std::endl;

int main() {
  std::thread t([] { cout << "Hi" << endl;});
  t.join();
  if (t.joinable()) // What happens if you comment out this line?
    t.join();
}
