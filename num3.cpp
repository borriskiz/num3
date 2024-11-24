#include "Tester.h"

int main() {
  srand(static_cast<unsigned int>(time(0)));

  while (1) {
    size_t n;
    std::cout << "Test N: ";
    std::cin >> n;
    Tester::makeTest(n);
    std::cout << "\n\n";
  }

  return 0;
}
