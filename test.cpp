#include "freshnbody.hpp"
#include <iostream>

int main() {
  using namespace fnb;
  constexpr Vec3 a = Vec3{1, 2, 3} + Vec3{4, 5, 6};
  std::cout << a.x << ' ' << a.y << ' ' << a.z << '\n';
  return 0;
}