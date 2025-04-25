#ifndef JEGY_H
#define JEGY_H

#include "String.h"
#include "Vonat.h"

class Jegy {
    Vonat* vonat;
    int kocsiszam;
    String hely;
    double ar;
    String kedvezmenyek;
    int kocsiosztaly;
    bool retur;
    String elado_allomas;
public:
    Jegy(Vonat* v = nullptr, 
        int ksz = 0, 
        const char* h = "", 
        double ar = 0.0, 
        const char* k = "",
        int ko = 3,
        bool r = false,
        const char* ea = ""): vonat(v), kocsiszam(ksz), hely(h),
        ar(ar), kedvezmenyek(k), kocsiosztaly(ko), retur(r), elado_allomas(ea) {}
    Jegy(const Jegy& j);
    bool operator==(const Jegy& j) const;
    bool operator!=(const Jegy& j) const;
    bool operator>(const Jegy& j)  const;
    bool operator<(const Jegy& j)  const;
    String operator[](const String& attr) const;
    
    template <typename T>
    T get(const String& attr);
};

#endif