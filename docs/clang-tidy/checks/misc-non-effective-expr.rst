misc-non-effective-expr
=======================

This checker reports cases whereby there is a variable or function call
in an expression, but regardless of its value the expression always evaluates to the same value.

	* if (false && myvar) always evaluates to false
	* if (true || myvar) always evaluates to true
	* if (0 & myvar) always evaluates to 0
	* if (0 && myvar) always evaluates to false
