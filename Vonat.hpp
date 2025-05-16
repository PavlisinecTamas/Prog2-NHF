#ifndef VONAT_H
#define VONAT_H

#include "String.h"

class Vonat {
    int vonatszam;
    String indulasi_allomas;
    String indulasi_ido;
    String erkezesi_allomas;
    String erkezesi_ido;
public:
    Vonat(int vszam = 0,
        const char* ind_a = "",
        const char* ind_i = "",
        const char* erk_a = "",
        const char* erk_i = ""): vonatszam(vszam), indulasi_allomas(ind_a), indulasi_ido(ind_i),
        erkezesi_allomas(erk_a), erkezesi_ido(erk_i) {}
    Vonat(const Vonat& v);
    String operator[](const String& attr) const;

    
    enum class VonatAttr {
        vonatszam,
        indulasi_allomas,
        indulasi_ido,
        erkezesi_allomas,
        erkezesi_ido,
        ismeretlen
    };

    std::exception hibas_tipus = std::invalid_argument("Hibas template parameter");
    std::exception nincs_mezo = std::invalid_argument("A Jegy osztalynak nincs ilyen mezoje");

    
    VonatAttr toVonatAttr(const String& a) const;

    template <typename T>
    T& get(const String& attr){
        VonatAttr vonatA = this->toVonatAttr(attr);

        if (vonatA == VonatAttr::ismeretlen) throw nincs_mezo;
        throw hibas_tipus;
    }
};

template<>
String& Vonat::get<String>(const String& attr);

template<>
int& Vonat::get<int>(const String& attr);
#endif
