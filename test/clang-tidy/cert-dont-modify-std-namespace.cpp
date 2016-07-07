// RUN: %check_clang_tidy %s cert-msc53-cpp %t -- -- -std=c++1z

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

namespace posix {
// CHECK-MESSAGES: :[[@LINE-1]]:11: warning: Modification of posix namespace can result to undefined behavior [cert-msc53-cpp]
  namespace vmi {
  }
}

namespace std {
// CHECK-MESSAGES: :[[@LINE-1]]:11: warning: Modification of std namespace can result to undefined behavior [cert-msc53-cpp]  
  int stdInt;
}

namespace foobar {
  namespace std {
// CHECK-MESSAGES: :[[@LINE-1]]:13: warning: Modification of std namespace can result to undefined behavior [cert-msc53-cpp]  
  }
}

namespace posix::a {
// CHECK-MESSAGES: :[[@LINE-1]]:11: warning: Modification of posix namespace can result to undefined behavior [cert-msc53-cpp]
}

using namespace std;

int main() {
  A::B::b = 6;
  A::B::c = 7;

  return 0;
}

