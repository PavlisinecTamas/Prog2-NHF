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
        const char* erk_i = ""): vonatszam(vszam), indulasi_allomas(ind_a),
        erkezesi_allomas(erk_a), erkezesi_ido(erk_i) {}
    Vonat(const Vonat& v);
    String operator[](const String& attr) const;

    template <typename T>
    T get(const String& attr);
};

#endif
