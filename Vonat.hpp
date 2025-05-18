#ifndef VONAT_H
#define VONAT_H
/**
 *  \file Vonat.hpp
 * 
 * Ez a fájl tartalmazza a Vonat osztály deklarációját
 */
#include "String.h"

/// @brief A vonatokat modellező osztály
class Vonat {
    int vonatszam;                      ///< A vonat száma
    String indulasi_allomas;            ///< Állomás ahonnan a vonat indul
    String indulasi_ido;                ///< Indulási idő
    String erkezesi_allomas;            ///< Állomás ahová a vonat érkezik
    String erkezesi_ido;                ///< Érkezési idő
public:
    /// @brief Konstruktor, alapértékeket ad felülírhatóan
    /// @param vszam - Vonatszám
    /// @param ind_a - Állomás ahonnan a vonat indul ("")
    /// @param ind_i - Indulási idő ("")
    /// @param erk_a - Állomás ahová a vonat érkezik ("")
    /// @param erk_i - Érkezési idő ("")
    Vonat(int vszam = 0,
        const char* ind_a = "",
        const char* ind_i = "",
        const char* erk_a = "",
        const char* erk_i = ""): vonatszam(vszam), indulasi_allomas(ind_a), indulasi_ido(ind_i),
        erkezesi_allomas(erk_a), erkezesi_ido(erk_i) {}
    
    /// @brief Másoló konstruktor
    /// @param v - vonat amit másolunk
    Vonat(const Vonat& v): vonatszam(v.vonatszam), indulasi_allomas(v.indulasi_allomas), indulasi_ido(v.indulasi_ido),
        erkezesi_allomas(v.erkezesi_ido), erkezesi_ido(v.erkezesi_ido) {}

    /// @brief Vonat osztály egy mezőjének elérése
    /// @param attr - mező neve
    /// @return Vonat osztály egy mezőjének Stringbe sorosított értéke
    String operator[](const String& attr) const;

    /// @brief Vonat mezőit azonosító típusok
    enum class VonatAttr {
        vonatszam = 1,
        indulasi_allomas = 2,
        indulasi_ido = 3,
        erkezesi_allomas = 4,
        erkezesi_ido = 5,
        ismeretlen = 6
    };

    /// @brief kivételek a get<T> templatenak
    std::exception hibas_tipus = std::invalid_argument("Hibas template parameter");
    /// @brief kivételek a get<T> templatenak
    std::exception nincs_mezo = std::invalid_argument("A Vonat osztalynak nincs ilyen mezoje");

    /// @brief mezőt nevesítő Stringből megfelelő típust hoz létre
    /// @param a - mezőt nevesítő String
    /// @return VonatAttr a megfelelő mezőhoz vagy VonatAttr::ismeretlen ha nincs ilyen mező
    VonatAttr toVonatAttr(const String& a) const;

    /// @brief mezőt nevesítő String alapján referenciát ad arra a mezőre
    /// @tparam T - a mező típusa
    /// @param attr - mezőt nevesítő String
    /// @return referencia a nevesített mezőre
    /// helytelen típus vagy nem létező mezőnév megadása esetén kivételt dob
    template <typename T>
    T& get(const String& attr){
        VonatAttr vonatA = this->toVonatAttr(attr);

        if (vonatA == VonatAttr::ismeretlen) throw nincs_mezo;
        throw hibas_tipus;
    }
};

/// @brief get<T> template specializáció String típusra
template<>
String& Vonat::get<String>(const String& attr);

/// @brief get<T> template specializáció int típusra
template<>
int& Vonat::get<int>(const String& attr);
#endif
