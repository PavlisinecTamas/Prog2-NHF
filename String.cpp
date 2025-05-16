#include <iostream>
#include <cstring>

#include "String.h"

String::String(char c) {
    hossz = 1;
    pData = new char[hossz + 1];
    pData[0] = c;
    pData[1] = '\0';
}

String::String(const char *p) {
    hossz = std::strlen(p);
    pData = new char[hossz + 1];
    strcpy(pData, p);
}

String::String(const String& s1) {
    hossz = s1.hossz;
    pData = new char[hossz + 1];
    strcpy(pData, s1.pData);
}


String& String::operator=(const String& rhs_s) {
    if (this == &rhs_s)
        return *this;

    delete[] pData;
    hossz = rhs_s.hossz;
    pData = new char[hossz + 1];
    strcpy(pData, rhs_s.pData);

    return *this;
}

String String::operator+(const String& rhs_s) const {
    String temp;
    temp.hossz = hossz + rhs_s.hossz;

    delete[] temp.pData;
    temp.pData = new char[temp.hossz + 1];
    strcpy(temp.pData, this->pData);
    strcat(temp.pData, rhs_s.pData);

    return temp;
}

String String::operator+(char c) const {
    return *this + String(c);
}

char& String::operator[](size_t idx) {
    if (idx >= hossz)
        throw "String túlindexelés";
    return pData[idx];
}

const char& String::operator[](size_t idx) const{
    if (idx >= hossz)
        throw "String túlindexelés";
    return pData[idx];
}


std::ostream& operator<<(std::ostream& os, const String& str) {
    os << str.c_str();
    return os;
}

std::istream& operator>>(std::istream& is, String& s0) {
    unsigned char ch;
    s0 = String("");            // üres string, ehhez fűzünk hozzá
	std::ios_base::fmtflags fl = is.flags(); // eltesszük a régi flag-eket
	is.setf(std::ios_base::skipws);			// az elején eldobjuk a ws-t
    while (is >> ch) {
	    is.unsetf(std::ios_base::skipws);	// utána pedig már nem
        if (isspace(ch)) {
            is.putback(ch);             // na ezt nem kérjük
            break;
        } else {
            s0 = s0 + ch;               // végére fűzzük a karaktert
        }
    }
	is.setf(fl);						// visszaállítjuk a flag-eket
    return is;
}

String operator+(char c, const String& str) {
    return String(c) + str;
}