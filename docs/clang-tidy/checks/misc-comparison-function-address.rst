.. title:: clang-tidy - misc-comparison-function-address

misc-comparison-function-address
================================

This Checker gives a warning if address of a function is compared.
For example: the programmer wants to write ``getc()==0`` but writes ``getc==0``

.. code-block:: c++ 
  if (getc== 0); // warning: Address of strlen is compared

but comparison to function pointer should be allowed

.. code-block:: c++
  int (* myfp)(char const * ) = 0;
  if (getc ==myfp); // should be ok

as a general rule, function pointers can be compared to other function pointers, function, 0, nullptr
functions can be compared only against function pointers
