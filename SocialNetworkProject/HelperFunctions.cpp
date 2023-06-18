#include "HelperFunctions.h"

void readString(std::istream& in, String& str)
{
    size_t strLen;
    char* ptr;
    in >> strLen;
    if (!in) {
        return;
    }
    in.ignore();
    ptr = new char[strLen + 1];
    in.get(ptr, strLen + 1);
    ptr[strLen] = '\0';
    str = String(ptr);
    delete[] ptr;
}
unsigned numLen(unsigned a) {
    unsigned len = 1;
    while (a>9)
    {
        a /= 10;
        len++;
    }
    return len;
}
String intToString(unsigned a) {
    unsigned len = numLen(a);
    char* ptr = new char[len + 1];
    for (unsigned i = 1;i <= len; i++)
    {   
        ptr[len - i] = a % 10+'0';
        a /= 10;
    }
    ptr[len] = '\0';
    String str(ptr);
    delete[]ptr;
    return str;
}

bool isPrefix(const char* pattern, const char* text)
{
    while (*text != '\0' && *pattern != '\0')
    {
        if (*text != *pattern)
            return false;
        text++;
        pattern++;
    }
    return *pattern == '\0';
}
bool searchInText(const char* text, const char* pattern)
{
    size_t textLen = strlen(text);
    size_t patternLen = strlen(pattern);
    while (patternLen <= textLen)
    {
        if (isPrefix(pattern, text))
            return true;
        text++;
        textLen--;
    }
    return false;
}