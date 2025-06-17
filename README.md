**CString (C String Manipulation Library)**

---

**Overview**
CString is a utility library that provides a safer, higher-level abstraction over raw C strings. It simplifies string manipulation, memory management, and comparison operations in C.

**Features**

* Easy string creation via macros
* String concatenation, slicing, and comparison
* Memory-safe: automatic cleanup via reference tracking
* Custom allocators for advanced use cases

**Requirements**

* clang or compatible C compiler

**Compilation**
Run `make` in the root directory to build the library.

**Example Usage**

```c
#include "cstring.h"

int main() {
  CString_InitInstanceCounter();
  CString *str = CSTR(Hello, World!);
  CString *str1 = CString_SubString(0, 5, str);
  CString *str2 = CString_FromCat(str1, CSTR(, Mom!));

  CString_PrintLine(str);     // Hello, World!
  CString_PrintLine(str1);    // Hello
  CString_PrintLine(str2);    // Hello, Mom!

  CString_DestroyInstances();
  return 0;
}
```

**Notes**

* Strings allocated via `CSTR` are automatically managed unless explicitly freed.
