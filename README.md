# Example project on std::thread
## Overview
My goal was to try the std::thread features by computing matrix product using multiple threads.
The first and the simplest way to perform matrix product that came to my mind was to split second matrix into columns
and perform matrix product separately for those columns. The way is correct as columns, received via matrix product are independent and I don't 
have to syncronize anything but provide shared container for result
## Tools
* Compiler: g++
* Build automation: make
* Unit testing: gtest library
* Misc:
  * Valgrind for memory check
  * CppCheck linter for static code analysis
  * gcc code sanitizers also for memory check and undefined behavior, which are enabled by specific options in Makefile
## Other
Also I have tried **ranges** library, which provides some great features likes **iota_view**, which enables users to get rid of anoying 
from x to y integer loops
