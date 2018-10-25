#include <functional>
#include <iostream>

int main(int argc, char *argv[]) {
  int a = 7;
  std::function<void(void)> f;
  f = [&a]() { std::cout << a << "\n"; };
  f();
  a = 8; // update parameter that has been passed by ref
  f();
  return 0;
}
