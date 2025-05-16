#ifndef JEGY_H
#define JEGY_H

#include "String.h"
#include "Vonat.hpp"

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
    Jegy(Vonat* v = NULL, 
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
    
    enum class JegyAttr {
        vonat,
        kocsiszam,
        hely,
        ar,
        kedvezmenyek,
        kocsiosztaly,
        retur,
        elado_allomas,
        ismeretlen
    };

    std::exception hibas_tipus = std::invalid_argument("Hibas template parameter");
    std::exception nincs_mezo = std::invalid_argument("A Jegy osztalynak nincs ilyen mezoje");

    JegyAttr toJegyAttr(const String& a) const;

    template<typename T>
    T& get(const String& attr) {
        JegyAttr jegyA = this->toJegyAttr(attr);

        if (jegyA == JegyAttr::ismeretlen) throw nincs_mezo;
        throw hibas_tipus;
    }
};

template<>
Vonat*& Jegy::get<Vonat*>(const String& attr);

template<>
String& Jegy::get<String>(const String& attr);

template<>
int& Jegy::get<int>(const String& attr);

template<>
double& Jegy::get<double>(const String& attr);

template<>
bool& Jegy::get<bool>(const String& attr);

#endif