// RUN: %check_clang_tidy %s misc-string-constructor %t

namespace std {
template <typename T>
class allocator {};
template <typename T>
class char_traits {};
template <typename C, typename T = std::char_traits<C>, typename A = std::allocator<C> >
struct basic_string {
  basic_string();
  basic_string(const C*, unsigned int size);
  basic_string(unsigned int size, C c);
};
typedef basic_string<char> string;
typedef basic_string<wchar_t> wstring;
}

const char* kText = "";
const char kText2[] = "";
extern const char kText3[];

void Test() {
  std::string str('x', 4);
  // CHECK-MESSAGES: [[@LINE-1]]:15: warning: constructor parameters are probably swapped [misc-string-constructor]
  std::wstring wstr(L'x', 4);
  // CHECK-MESSAGES: [[@LINE-1]]:16: warning: constructor parameters are probably swapped
  std::string s0(0, 'x');
  // CHECK-MESSAGES: [[@LINE-1]]:15: warning: constructor creating an empty string
  std::string s1(-4, 'x');
  // CHECK-MESSAGES: [[@LINE-1]]:15: warning: negative value used as length parameter
  std::string s2(0x1000000, 'x');
  // CHECK-MESSAGES: [[@LINE-1]]:15: warning: suspicious large length parameter
  
  std::string q0("test", 0);
  // CHECK-MESSAGES: [[@LINE-1]]:15: warning: constructor creating an empty string
  std::string q1(kText, -4);
  // CHECK-MESSAGES: [[@LINE-1]]:15: warning: negative value used as length parameter
  std::string q2("test", 200);
  // CHECK-MESSAGES: [[@LINE-1]]:15: warning: length is bigger then string literal size
  std::string q3(kText, 200);
  // CHECK-MESSAGES: [[@LINE-1]]:15: warning: length is bigger then string literal size
  std::string q4(kText2, 200);
  // CHECK-MESSAGES: [[@LINE-1]]:15: warning: length is bigger then string literal size
  std::string q5(kText3,  0x1000000);
  // CHECK-MESSAGES: [[@LINE-1]]:15: warning: suspicious large length parameter
}

void Valid() {
  std::string empty();
  std::string str(4, 'x');
  std::wstring wstr(4, L'x');
  std::string s1("test", 4);
  std::string s2("test", 3);
}
