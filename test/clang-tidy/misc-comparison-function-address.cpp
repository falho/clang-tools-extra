// RUN: %check_clang_tidy %s misc-comparison-function-address %t

#define nullptr 0
#define NULL    0

struct __sFile {
  int unused;
};
  
typedef struct __sFILE FILE;

int getc(FILE * stream);
char func();
char * func2();


void test_function_warning() {
  if (getc == 0); 
  // CHECK-MESSAGES: :[[@LINE-1]]:12: warning: Address of function is compared [misc-comparison-function-address]
  
  if (0 == getc);
  // CHECK-MESSAGES: :[[@LINE-1]]:9: warning: Address of function is compared [misc-comparison-function-address]  
 
  if (getc == nullptr);
  // CHECK-MESSAGES: :[[@LINE-1]]:12: warning: Address of function is compared [misc-comparison-function-address]

  if (NULL == func);
  // CHECK-MESSAGES: :[[@LINE-1]]:12: warning: Address of function is compared [misc-comparison-function-address]
}


void test_function_awsome() {
  FILE * pFile;
  int (*myfp)(FILE *) = 0;
  char (*myfp2)();
  
  if (getc == myfp);

  if (0 == myfp);

  if (getc(pFile) == 0);

  if (myfp == getc);

  if (myfp == 0);

  if (myfp == NULL);

  if (func == myfp2);
}

