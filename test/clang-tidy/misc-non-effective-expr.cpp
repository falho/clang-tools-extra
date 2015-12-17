// RUN: %check_clang_tidy %s misc-non-effective-expr %t

void f(){
	bool myvar = true;
	if (false && myvar){
	}
	// CHECK-MESSAGES: :[[@LINE-2]]:6: warning: error: always evaluates to false [misc-non-effective-expr]
	if (true || myvar){
	}
	// CHECK-MESSAGES: :[[@LINE-2]]:6: warning: error: always evaluates to true
	if (0 & myvar){
	}
	// CHECK-MESSAGES: :[[@LINE-2]]:6: warning: error: always evaluates to 0
	if (0 && myvar){
	}
	// CHECK-MESSAGES: :[[@LINE-2]]:6: warning: error: always evaluates to false
}
