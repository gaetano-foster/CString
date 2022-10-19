#ifndef __ALLOCATOR_H__
#define __ALLOCATOR_H__
#include "stdlib.h"
typedef struct CString CString;

struct AllocatedString {
    int freed;
    CString *str;
};

struct StringInstanceCounter {
    size_t ref_count;
    size_t size;
    struct AllocatedString *allocated_strings;
};

extern struct StringInstanceCounter g_instancecounter;

#endif // __ALLOCATOR_H__