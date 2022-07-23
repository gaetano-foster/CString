# CString
## What is CString?
A library/wrapper around strings for C that allows easy string manipulation. Working with strings is often regarded as
a chore in C, and an unsafe one at that. This should help to ease some of the pain.
## Features
* Easy string concatenation functions.
* Easy string comparison.
* Macro for generating CStrings.
* Many ways to allocate new strings, including by copying and moving strings.
* No need to explicitly free CStrings (You still have the option to if you want)
* As well as other features.
More features should be coming soon.
## Compiling
### Prerequisites
You need clang installed on your computer.
### How to Compile
Type "make" in the terminal to compile the library.
## How to Use
Below is an example program which demonstrates most of the things the library can do:
```c
#include "cstring.h"

int main() {
  CString_InitInstanceCounter(); // enable automatic memory management of CStrings
  CString *str = CSTR(Hello, World!); // Creates new CString with value "Hello, World!" and length of 13
  CString *str1 = CString_SubString(0, 5, str); // Creates new string from first 5 elements of str, or "Hello"
  CString *str2 = CString_FromCat(str1, CSTR(, Mom!)); // Creates 2 new strings: the one returned from
                                                       // CString_FromCat, and the one returned from CSTR
                                                       // don't worry, any string allocated with CSTR macro
                                                       // will be automatically freed when CString_DestroyInstances
                                                       // is called, even when not assigned to a variable.
  CString_PrintLine(str);
  CString_PrintLine(str1);
  CString_PrintLine(str2);
  CString_DestroyInstances(); // free all memory allocated for strings that 
                              // has not been freed yet
  return 0;
}
// Expected Output:
// Hello, World!
// Hello
// Hello, Mom!
```
