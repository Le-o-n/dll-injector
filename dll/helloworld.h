// hello.h
// Define the HELLO_API macro that will be used to specify
// whether the function hello() should be exported or imported.
#ifdef HELLO_EXPORTS
#define HELLO_API __declspec(dllexport)
#else
#define HELLO_API __declspec(dllimport)
#endif

// Declare the hello() function using the HELLO_API macro.
// This tells the compiler that the function should be treated
// as an exported or imported symbol, depending on how the
// header file is included.
extern "C" HELLO_API void hello();

