#ifndef STRING_H
#define STRING_H

#include <iostream>

class String {
    char *pData;
    size_t hossz;
public:
    String(char c);
    String(const char *p = "");
    String(const String& s1);

    inline size_t size() const { return hossz; }
    inline const char* c_str() const { return pData; }
    
    String& operator=(const String& rhs_s);
    String operator+(const String& rhs_s) const;
    String operator+(char c) const;
    char& operator[](size_t idx);   
    const char& operator[](size_t idx) const;
    
    ~String() { delete[] pData; }
};


std::ostream& operator<<(std::ostream& os, const String& str);
std::istream& operator>>(std::istream& is, String& s0);

String operator+(char ch, const String& str);

#endif