// RUN: %check_clang_tidy %s misc-comparison-misuse %t

// FIXME: Add something that triggers the check here.
void f();
// CHECK-MESSAGES: :[[@LINE-1]]:6: warning: function 'f' is insufficiently awesome [misc-comparison-misuse]

// FIXME: Verify the applied fix.
//   * Make the CHECK patterns specific enough and try to make verified lines
//     unique to avoid incorrect matches.
//   * Use {{}} for regular expressions.
// CHECK-FIXES: {{^}}void awesome_f();{{$}}

// FIXME: Add something that doesn't trigger the check here.
void awesome_f2();


// RUN: $(dirname %s)/check_clang_tidy.sh %s misc-virtual-shadowing %t
// REQUIRES: shell

#define NULL __null


int strcmp(char *, char *);
int strncmp ( const char * str1, const char * str2, int num );
int memcmp ( const void * ptr1, const void * ptr2, int num );

bool isMyString(const char *my){
     bool b = (my=="mystring");//error. comparing pointer to string literal
     return "mystring"==my;//error. comparing pointer to string literal
}

char * testFunction(char * str1, char * str2) {
      if (strcmp(str1,str2)>0)//is correct
         return str1;

      if (strcmp(str1,str2)==1)//is incorrect
         return str2;
}

char * testFunction2(char * str1, char * str2) {
      if (strncmp(str1,str2,2)>0)//is correct
         return str1;

      if (strncmp(str1,str2,2)==1)//is incorrect
         return str2;
}

void tesFunction3() {
      char buffer1[] = "DWgaOtP12df0";
      char buffer2[] = "DWGAOTP12DF0";

      // this case should be solved as well
      int n=memcmp ( buffer1, buffer2, sizeof(buffer1) );
      if(n==1){}

      memcmp ( buffer1, buffer2, sizeof(buffer1) )<0;//is correct;
      memcmp ( buffer1, buffer2, sizeof(buffer1) )==1;//is incorrect
}

void testFunction3(int *p){
  if (NULL>=p);//error, use only NULL==p, NULL!=p
  if (NULL==p);
  if (NULL!=p);
}
                                    
