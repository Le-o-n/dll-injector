// hello.cpp
// Include the iostream library to provide the std::cout
// and std::endl objects used by the hello() function.
#include <iostream>

// Include the hello.h header file to get the declaration
// of the hello() function.
#include "helloworld.h"

// Implement the hello() function. This is the actual
// "Hello, world!" program that will be exported by the DLL.
void hello()
{
  // Print the "Hello, world!" message to the standard output stream.
  std::cout << "Hello, world!" << std::endl;
}