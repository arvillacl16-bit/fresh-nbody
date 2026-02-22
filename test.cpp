#include "freshnbody.hpp"
#include <iostream>

int main() {
  fnb::Vec3 a(1, 2, 3);
  std::cout << a.mag2() << '\n';
  return 0;
}