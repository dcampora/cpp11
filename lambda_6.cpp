
int main() {
  [](int x)->int{ 
    if (x<10)
      return x + 10;
    else
      return x * 2;
  }(3);

  [](int x)->int{ 
    if (x<10)
      return x + 10;
    else
      return x * 0.2;
  }(3);
}
