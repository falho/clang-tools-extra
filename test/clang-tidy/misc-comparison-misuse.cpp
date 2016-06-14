// RUN: %check_clang_tidy %s misc-comparison-misuse %t

#define NULL __null

bool test_pointer_to_literal(const char *my){
  bool b = (my=="mystring");
  // CHECK-MESSAGES: :[[@LINE-1]]:15: warning: char* is compared to a string literal [misc-comparison-misuse]
  return "mystring"==my;
  // CHECK-MESSAGES: :[[@LINE-1]]:20: warning: char* is compared to a string literal [misc-comparison-misuse]
}

void test_null_to_pointer(int *p){
  if (NULL>=p);
  // CHECK-MESSAGES: :[[@LINE-1]]:11: warning: comparison to nullptr [misc-comparison-misuse]
  
  if (NULL==p);
  
  if (NULL!=p);
}
                                    
