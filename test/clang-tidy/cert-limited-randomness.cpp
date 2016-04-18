// RUN: %check_clang_tidy %s cert-limited-randomness %t

namespace std {
int rand();
typedef char * string;
char * to_string(int);
}


int rand();

void noncompilant() {
  int i = std::rand();
  // CHECK-MESSAGES: :[[@LINE-1]]:16: warning: rand() function has limited randomness [cert-limited-randomness]

  int j = ::rand();
  // CHECK-MESSAGES: :[[@LINE-1]]:13: warning: rand() function has limited randomness [cert-limited-randomness]

  int k = rand();
  // CHECK-MESSAGES: :[[@LINE-1]]:11: warning: rand() function has limited randomness [cert-limited-randomness]
}


void f() {
  std::to_string(std::rand() % 10000);
  // CHECK-MESSAGES: :[[@LINE-1]]:23: warning: rand() function has limited randomness [cert-limited-randomness]
}
