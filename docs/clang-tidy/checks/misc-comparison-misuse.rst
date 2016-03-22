.. title:: clang-tidy - misc-comparison-misuse

misc-comparison-misuse
======================

This checker reports errors related to the misuse of the comparison operator.
It should warn for the following cases


Case 1:
strcmp,strncmp,memcmp misuse.
strcmp(const char* str1,const char* str2);

These operators return by
   >0 if str1>str2
   <0 if str1<str2
   =0 if str1==str2

Example:
  //strcmp,strncmp,memcmp
  //Thus
  if (strcmp(str1,str2)>0)//is correct
    printf(str1);

  if (strcmp(str1,str2)==1)//is incorrect
    printf(str1);


Case 2:
char* is compared to a string literal

Example:
  bool isMyString(const char * my){
    return "mystring"==my;//error. comparing pointer to string literal
  }


Case 3:
inequality operator usage for NULL

Example:
  void(int * p){
    if (NULL>=p)//error, use only NULL==p, NULL!=p
  }

