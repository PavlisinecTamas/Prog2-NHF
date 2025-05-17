/**
 * \file String.cpp
 */
#include <iostream>
#include <cstring>

#include "String.h"

/// konstrktor karakterből
String::String(char c) {
    hossz = 1;                      
    pData = new char[hossz + 1];
    pData[0] = c;
    pData[1] = '\0';
}

/// Konstruktor egy nullával lezárt karaktersorozatból
String::String(const char *p) {
    hossz = std::strlen(p);
    pData = new char[hossz + 1];
    strcpy(pData, p);
}

/// Másoló konstruktor
String::String(const String& s1) {
    hossz = s1.hossz;
    pData = new char[hossz + 1];
    strcpy(pData, s1.pData);
}

/// Értékadó operátor
String& String::operator=(const String& rhs_s) {
    if (this == &rhs_s)
        return *this;

    delete[] pData;
    hossz = rhs_s.hossz;
    pData = new char[hossz + 1];
    strcpy(pData, rhs_s.pData);

    return *this;
}

/// Két stringet összefűz
String String::operator+(const String& rhs_s) const {
    String temp;
    temp.hossz = hossz + rhs_s.hossz;

    delete[] temp.pData;
    temp.pData = new char[temp.hossz + 1];
    strcpy(temp.pData, this->pData);
    strcat(temp.pData, rhs_s.pData);

    return temp;
}

/// Stringhez karaktert fűz
String String::operator+(char c) const {
    return *this + String(c);
}

/// A String adott indexű karakterét adja vissza
char& String::operator[](size_t idx) {
    if (idx >= hossz)
        throw "String túlindexelés";
    return pData[idx];
}

/// A String adott indexű karakterét adja vissza
const char& String::operator[](size_t idx) const{
    if (idx >= hossz)
        throw "String túlindexelés";
    return pData[idx];
}

/// Stringet ír az ostream-re
std::ostream& operator<<(std::ostream& os, const String& str) {
    os << str.c_str();
    return os;
}

/// istream-ről egy szót olvas be Stringbe
std::istream& operator>>(std::istream& is, String& s0) {
    unsigned char ch;
    s0 = String("");
	std::ios_base::fmtflags fl = is.flags();
	is.setf(std::ios_base::skipws);			
    while (is >> ch) {
	    is.unsetf(std::ios_base::skipws);
        if (isspace(ch)) {
            is.putback(ch);
            break;
        } else {
            s0 = s0 + ch;
        }
    }
	is.setf(fl);
    return is;
}

/// Karakterhez Stringet fűz
String operator+(char c, const String& str) {
    return String(c) + str;
}