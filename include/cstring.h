#ifndef __CSTRING_H__
#define __CSTRING_H__
#include <stdio.h>
#include <stdlib.h>
#define CSTR(...)                       CString_Infer(#__VA_ARGS__)

typedef struct CString {
    char *m_buf; // string buffer
    size_t length; // length (does NOT include null terminator)
    int id; // for memory allocation tracking
} CString;

void CString_InitInstanceCounter(void); // call as soon as program begins
void CString_DestroyInstances(void); // free all strings (call when program ends)
void CString_InstancePushBack(CString *instance);

CString* CString_New(const char *buffer, size_t length);
CString* CString_Infer(const char *buffer); // same as CString_New but uses strlen internally, making it less safe
CString* CString_Copy(CString *other);
CString* CString_Move(CString *other);
CString* CString_FromCat(CString *str1, CString *str2); // dest + src (creates new string that needs to be freed)
CString* CString_SubString(size_t start, size_t end, const CString *str);
CString* CString_FromInt(int value);
CString* CString_FromFraction(double value);
CString* CString_FromHex(int value);
CString* CString_FromOctal(int value);

void CString_Free(CString *str);
void CString_Append(CString *dest, CString *src); // dest += src
int CString_Equals(CString *str1, CString *str2);
char CString_At(CString *str, size_t index);
int CString_Write(FILE *stream, CString *str); // writes to file
int CString_Print(CString *str); // writes to stdout
int CString_PrintLine(CString *str); // writes to stdout with newline character

#endif // __CSTRING_H__