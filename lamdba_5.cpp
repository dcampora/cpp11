
#include <iostream>    // cout, cin, endl
#include <algorithm>   // generate
#include <string>      // string
#include <vector>      // vector
#include <functional>  // function

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::function;

// Consider the MenuItem, Menu and Lift classes to have been provided
// by a library. Your job is to simplify the client code by replacing
// the functors with lambda expressions.
class MenuItem {
public:
  MenuItem(string l, function<void()> a) : label(l), action(a) {}
  string get_label() const { return label; }
  void doit() const { action(); }
  void display() const { cout << label << endl; }
private:
  string label;
  function<void()> action;
};

class Menu {
public:

  void display() {
    int count = 0;
    for (auto item:items) {
      cout << ++count << ". ";
      item.display();
    }
  }

  void add_item(string l, function<void()> a) { items.push_back(MenuItem(l, a)); }

  void select(unsigned int choice) {
    if (1 <= choice && choice <= items.size())
      items[choice-1].doit();
    else
      cout << "Invalid choice " << choice << endl;
  }

private:
  std::vector<MenuItem> items;
};

class Lift {
public:
  Lift(unsigned int id_) : id(id_), level(0) {}
  void up()           { ++level; }
  void down()         { --level; }
  void report() const { cout << "Lift " << id << " is on level " << level << endl; }
private:
  unsigned int id;
  int level;
};

// Don't change the code above this line
////////////////////////////////////////////////////////////////////////////////
// Simplify the code below, by replacing functors with lambda expressions

int main() {
  std::vector<Lift> lifts{Lift(1), Lift(2)};

  struct LiftUP {
    LiftUP(decltype(lifts)& lifts, int n) : lifts(lifts), n(n) {}
    void operator() () { lifts[n].up(); }
  private:
    decltype(lifts)& lifts;
    int n;
  };

  struct LiftDOWN {
    LiftDOWN(decltype(lifts)& lifts, int n) : lifts(lifts), n(n) {}
    void operator() () { lifts[n].down(); }
  private:
    decltype(lifts)& lifts;
    int n;
  };

  struct Report {
    Report(decltype(lifts)& lifts) : lifts(lifts) {}
    void operator () () { 
      for (auto lift:lifts) lift.report();
    }
  private:
    decltype(lifts)& lifts;
  };

  struct QUIT { 
    QUIT(bool& quit) : quit(quit) {}
    void operator() () { quit = true; }
  private:
    bool& quit;
  };

  Menu menu;
  menu.add_item("Lift 1 up",   LiftUP  (lifts, 0));
  menu.add_item("Lift 1 down", LiftDOWN(lifts, 0));
  menu.add_item("Lift 2 up",   LiftUP  (lifts, 1));
  menu.add_item("Lift 2 down", LiftDOWN(lifts, 1));
  menu.add_item("Report",      Report  (lifts));

  bool quit = false;
  menu.add_item("QUIT", QUIT(quit));

  while (!quit) {
    menu.display();
    int choice;
    cin >> choice;
    menu.select(choice);
  }

}
