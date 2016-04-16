// RUN: %check_clang_tidy %s misc-comparison-misuse %t

#define NULL __null

int strcmp(char *, char *);
int strncmp ( const char * str1, const char * str2, int num );
int memcmp ( const void * ptr1, const void * ptr2, int num );

bool test_pointer_to_literal(const char *my){
  bool b = (my=="mystring");
  // CHECK-MESSAGES: :[[@LINE-1]]:15: warning: char* is compared to a string literal [misc-comparison-misuse]
  return "mystring"==my;
  // CHECK-MESSAGES: :[[@LINE-1]]:20: warning: char* is compared to a string literal [misc-comparison-misuse]
}


char * test_strcmp(char * str1, char * str2) {
  int i = 8;     

  if (strcmp(str1,str2)>0)
     return str1;

  if (strcmp(str1,str2)==1)
  // CHECK-MESSAGES: :[[@LINE-1]]:24: warning: function should be compared only to 0 [misc-comparison-misuse]
     return str2;

  if (strcmp(str1,str2)==i)
  // CHECK-MESSAGES: :[[@LINE-1]]:24: warning: function should be compared only to 0 [misc-comparison-misuse]
     return str2;

  int h = strcmp(str1,str2); // has to be fixed, checker wont match...
  if(h==1);
}


char * test_strncmp(char * str1, char * str2) {
  int i = 8;

  if (strncmp(str1,str2, 2)>0)
     return str1;
    
  if (strncmp(str1,str2, 3)==1)
  // CHECK-MESSAGES: :[[@LINE-1]]:28: warning: function should be compared only to 0 [misc-comparison-misuse]
     return str2;

  if (strncmp(str1,str2, 4)==i)
  // CHECK-MESSAGES: :[[@LINE-1]]:28: warning: function should be compared only to 0 [misc-comparison-misuse]
     return str2;

  int h = strncmp(str1,str2, 2); 
  if(h==1); // has to be fixed, matcher won't match
}


void test_memcmp() {
  char buffer1[] = "DWgaOtP12df0";
  char buffer2[] = "DWGAOTP12DF0";

  memcmp ( buffer1, buffer2, sizeof(buffer1) )<0;

  memcmp ( buffer1, buffer2, sizeof(buffer1) )==1;
  // CHECK-MESSAGES: :[[@LINE-1]]:47: warning: function should be compared only to 0 [misc-comparison-misuse]
  
  int i = 7;
  memcmp(buffer1, buffer2, sizeof(buffer1) ) == i;
  // CHECK-MESSAGES: :[[@LINE-1]]:46: warning: function should be compared only to 0 [misc-comparison-misuse] 

  int n=memcmp ( buffer1, buffer2, sizeof(buffer1) );
  if(n==1){} // has to be fixed, checker won't match
}


void test_null_to_pointer(int *p){
  if (NULL>=p);
  // CHECK-MESSAGES: :[[@LINE-1]]:11: warning: comparison to nullptr [misc-comparison-misuse]
  
  if (NULL==p);
  
  if (NULL!=p);
}
                                    
