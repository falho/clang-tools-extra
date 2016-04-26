// RUN: %check_clang_tidy %s cert-msc50-cpp %t

int rand();

namespace std {
using ::rand;
typedef char * string;
char * to_string(int);
}

//#include <cstdlib>

namespace nonstd {
  int rand();
}

// problem: matcher is also matching for this
//int rand(int);

void testFunction1() {
  int i = std::rand();
  // CHECK-MESSAGES: :[[@LINE-1]]:16: warning: rand() function has limited randomnes, use C++11 random library instead [cert-msc50-cpp]

  int j = ::rand();
  // CHECK-MESSAGES: :[[@LINE-1]]:13: warning: rand() function has limited randomness, use C++11 random library instead [cert-msc50-cpp]

  //int k = rand(i);
  // CHECK-MESSAGES: :[[@LINE-1]]:11: warning: rand() function has limited randomness, use C++11 random library instead [cert-msc50-cpp]

  int l = nonstd::rand();

  int m = rand();
}

