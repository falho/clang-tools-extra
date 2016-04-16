.. title:: clang-tidy - misc-comparison-function-address

misc-comparison-function-address
================================

This Checker gives a warning if address of a function is compared.
For example: the programmer wants to write getc()==0 but writes getc==0

if (getc== 0)...//error. Address of strlen is compared
but comparison to function pointer should be allowed

int (* myfp)(char const * ) = 0;i
if (getc ==myfp)//should be ok

as a general rule, function pointers can be compared to other function pointers, function, 0, nullptr
functions can be compared only against function pointers
