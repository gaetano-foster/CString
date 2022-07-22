#include "allocator.h"
#include "cstring.h"

struct StringInstanceCounter g_instancecounter;

void CString_InitInstanceCounter(void) {
    g_instancecounter.ref_count = 0;
    g_instancecounter.size = 1;
    g_instancecounter.allocated_strings = malloc(sizeof(struct AllocatedString)*g_instancecounter.size);
}

void CString_DestroyInstances(void) {
    for (int i = 0; i < g_instancecounter.ref_count; i++) {
        if (!g_instancecounter.allocated_strings[i].freed)
            CString_Free(g_instancecounter.allocated_strings[i].str);
    }
    free(g_instancecounter.allocated_strings);
}

void CString_InstancePushBack(CString *instance) {
    instance->id = g_instancecounter.ref_count;
    g_instancecounter.allocated_strings[g_instancecounter.ref_count].str = instance;
    g_instancecounter.allocated_strings[g_instancecounter.ref_count].freed = 0;
    g_instancecounter.ref_count++;
    if (g_instancecounter.ref_count >= g_instancecounter.size) {
        g_instancecounter.size *= 2;
        g_instancecounter.allocated_strings = realloc(g_instancecounter.allocated_strings, sizeof(struct AllocatedString)*g_instancecounter.size);
    }
}
