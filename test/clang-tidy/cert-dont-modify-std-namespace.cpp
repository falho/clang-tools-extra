// RUN: %check_clang_tidy %s cert-msc53-cpp %t

//#include <iostream>

namespace A {
  namespace B {
    int b;
  }
}

namespace A {
  namespace B {
    int c;
  }
}

namespace std {
// CHECK-MESSAGES: :[[@LINE-1]]:1: warning: modification of std namespace can result to undefined behavior [cert-msc53-cpp]  
  int stdInt;
}

using namespace std;

int main() {
  A::B::b = 6;
  A::B::c = 7;

  return 0;
}

