#include <cstdio>

// RUN: %check_clang_tidy %s misc-comparison-function-address %t

// FIXME: Add something that triggers the check here.
void f() {
  int var = 2;
  if (getc == 0)
    ; //error. Address of getc is compared
  if (var == getc)
    ;
  if (getc == nullptr)
    ;
}
// CHECK-MESSAGES: :[[@LINE-1]]:6: warning: function 'f' is insufficiently awesome [misc-comparison-function-address]

// FIXME: Verify the applied fix.
//   * Make the CHECK patterns specific enough and try to make verified lines
//     unique to avoid incorrect matches.
//   * Use {{}} for regular expressions.
// CHECK-FIXES: {{^}}void awesome_f();{{$}}

// FIXME: Add something that doesn't trigger the check here.
void awesome_f2() {
  int (*myfp)(char const *) = 0;
  if (getc == myfp)
    ; //should be ok
  if (0 == myfp)
    ;
  if (getc("myString") == 0)
    ;
  if (myfp == getc)
    ;
  if (0 == getc)
    ;
  if (myfp == 0)
    ;
  if (myfp == NULL)
    ;
}

