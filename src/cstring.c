#include "cstring.h"
#include "allocator.h"
#include <string.h>

CString* CString_New(const char *buffer, size_t length) {
    CString *new = malloc(sizeof(CString));
    new->m_buf = malloc((length+1)*sizeof(char)); // allocate extra character for null terminator
    new->length = length;

    for (int i = 0; i < (length+1); i++) {
        new->m_buf[i] = buffer[i];
    }
    new->m_buf[length] = '\0'; // to ensure null termination
    CString_InstancePushBack(new);

    return new;
}

CString* CString_Infer(const char *buffer) {
    return CString_New(buffer, strlen(buffer));
}

CString* CString_Copy(CString *other) {
    return CString_Infer(other->m_buf);
}

CString* CString_Move(CString *other) {
    CString *new = malloc(sizeof(CString));
    new->m_buf = other->m_buf;
    new->length = other->length;
    other->m_buf = NULL;
    other->length = 0;
    free(other);
    g_instancecounter.allocated_strings[other->id].freed = 1;
    CString_InstancePushBack(new);
    return new;
}

CString* CString_FromCat(CString *str1, CString *str2) {
    CString *new = malloc(sizeof(CString));
    new->m_buf = malloc((str1->length+str2->length+1)*sizeof(char));
    new->length = str1->length+str2->length;

    for (int i = 0; i < str1->length; i++) {
        new->m_buf[i] = str1->m_buf[i];
    }

    for (int i = str1->length; i < (new->length+1); i++) {
        new->m_buf[i] = str2->m_buf[i-str1->length];
    }
    new->m_buf[new->length] = '\0';
    CString_InstancePushBack(new);

    return new;
}

CString* CString_SubString(size_t start, size_t end, const CString *str) {
    CString *new = malloc(sizeof(CString));

    if (start > end) {
        size_t temp = start;
        start = end;
        end = temp;
    }
    if (start == end) {
        end += 1;
    }

    new->length = end - start;
    new->m_buf = malloc((new->length+1)*sizeof(char));

    for (int i = start; i < end; i++) {
        new->m_buf[i-start] = str->m_buf[i];
    }
    new->m_buf[new->length] = '\0';
    CString_InstancePushBack(new);

    return new;
}

CString* CString_FromInt(int value) {
    char buf[30];
    sprintf(buf, "%d", value);
    return CString_Infer(buf);
}

CString* CString_FromFraction(double value) {
    char buf[30];
    sprintf(buf, "%f", value);
    return CString_Infer(buf);
}

CString* CString_FromHex(int value) {
    char buf[30];
    sprintf(buf, "0x%x", value);
    return CString_Infer(buf);
}

CString* CString_FromOctal(int value) {
    char buf[30];
    sprintf(buf, "0%o", value);
    return CString_Infer(buf);
}

CString** CString_Tokenize(CString *src, CString *sep, int *elements) {
    if (sep->length >= src->length) // what are you doing?
        return NULL;
    size_t array_size = 1;
    int begin = 0;
    int index = 0;
    CString **array = malloc(array_size*sizeof(CString*));
    for (int i = 0; i < src->length - sep->length; i++) {
        if (i == src->length - sep->length - 1) {
            array[index] = CString_SubString(begin, src->length, src);
            index++;
            begin = i + sep->length;
            if (index >= array_size) {
                array_size *= 2;
                array = realloc(array, array_size*sizeof(CString*));
            }
        }

        if (CString_Equals(CString_SubString(i, i+sep->length, src), sep)) {
            array[index] = CString_SubString(begin, i, src);
            index++;
            begin = i + sep->length;
            if (index >= array_size) {
                array_size *= 2;
                array = realloc(array, array_size*sizeof(CString*));
            }
        }
    }
    *elements = index;
    return array;
}

void CString_Append(CString *dest, CString *src) {
    size_t length_new = dest->length + src->length;
    dest->m_buf = realloc(dest->m_buf, (length_new+1)*sizeof(char));
    for (int i = dest->length; i < length_new; i++) {
        dest->m_buf[i] = src->m_buf[i-dest->length];
    }
    dest->m_buf[length_new] = '\0';
    dest->length = length_new;
}

int CString_Equals(CString *str1, CString *str2) {
    if (str1->length != str2->length)
        return 0;
    
    for (int i = 0; i < str1->length; i++) {
        if (str1->m_buf[i] != str2->m_buf[i])
            return 0;
    }
    return 1;
}

char CString_At(CString *str, size_t index) {
    if (index > str->length || index < 0)
        return '#';
    return str->m_buf[index];
}

int CString_Write(FILE *stream, CString *str) {
    str->m_buf[str->length] = '\0';
    return fprintf(stream, "%s", str->m_buf);
}

int CString_Print(CString *str) {
    return CString_Write(stdout, str);
}

int CString_PrintLine(CString *str) {
    return CString_Print(str) + printf("\n");
}

void CString_Free(CString *str) {
    g_instancecounter.allocated_strings[str->id].freed = 1;
    free(str->m_buf);
    free(str);
}
