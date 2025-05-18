#ifndef JEGY_H
#define JEGY_H

/**
 * \file Jegy.hpp
 * 
 * Ez a fájl tartalmazza a Jegy osztály deklarációját.
 */

#include "String.h"
#include "Vonat.hpp"

/**
 * Jegy osztály.
 * 
 * A mezők a specifikációnak megfelelően tartalmazzák az adatokat.
 */
class Jegy {
    Vonat* vonat;                   ///< pointer a vonatra amelyikre a jegy szól
    int kocsiszam;                  ///< kocsiszám a vonaton
    String hely;                    ///< hely a vonaton
    double ar;                      ///< a jegy ára
    String kedvezmenyek;            ///< Kedvezmények leírása (ha van)
    int kocsiosztaly;               ///< kocsiosztály (alapértelmezette 3)
    bool retur;                     ///< retur jegy-e ez a jegy
    String elado_allomas;           ///< állomás ahol a jegyet eladták
public:

    /// @brief Konstruktor ami alapértéket ad minden mezőnek
    /// @param v - vonat pointer (NULL)
    /// @param ksz - kocsiszám (0)
    /// @param h - hely ("")
    /// @param ar - ár (0.0)
    /// @param k - kedvezmények ("")
    /// @param ko - kocsiosztály (3)
    /// @param r - retur jegy-e (false)
    /// @param ea - állomás ahol a jegyet eladták ("")
    Jegy(Vonat* v = NULL, 
        int ksz = 0, 
        const char* h = "", 
        double ar = 0.0, 
        const char* k = "",
        int ko = 3,
        bool r = false,
        const char* ea = ""): vonat(v), kocsiszam(ksz), hely(h),
        ar(ar), kedvezmenyek(k), kocsiosztaly(ko), retur(r), elado_allomas(ea) {}

    /// @brief Másoló konstruktor
    /// @param j - jegy amit másolunk
    Jegy(const Jegy& j): vonat(j.vonat), kocsiszam(j.kocsiszam), hely(j.hely),
        ar(j.ar), kedvezmenyek(j.kedvezmenyek), kocsiosztaly(j.kocsiosztaly), retur(j.retur), elado_allomas(j.elado_allomas) {}

    /// @brief Két jegy minden mezőjének egynelőségét vizsgálja
    /// @param j - jegy amivel összehasonlítunk
    /// @return igaz ha a két jegy minden mezője egyenlő
    bool operator==(const Jegy& j) const;

    /// @brief két jegy minden mezőjének egyenlőségét vizsgálja
    /// @param j - jegy amivel összehasonlítunk
    /// @return igaz ha a két jegy bármely mezője nem egyenlő
    bool operator!=(const Jegy& j) const;

    /// @brief két jegy árának összehasonlítása
    /// @param j - jegy amivel összehasonlítunk
    /// @return igaz ha ennek a jegynek nagyobb az ára mint j jegynek
    bool operator>(const Jegy& j)  const;

    /// @brief két jegy árának összehasonlítása
    /// @param j - jegy amivel összehasonlítunk
    /// @return igaz ha ennek a jegynek nagyobb az ára mint j jegynek
    bool operator<(const Jegy& j)  const;

    /// @brief Jegy osztály egy mezőjének elérése 
    /// @param attr - mező neve
    /// @return Jegy osztály egy mezőjének Stringbe sorosított értéke
    /// ha nincs adott nevű mező a jegy osztályban akkor std::invalid_argument kivételt dob
    String operator[](const String& attr) const;
    
    /// @brief Jegy mezőit azonosító típusok
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

    /// @brief kivételek a get<T> templatenak
    std::invalid_argument hibas_tipus = std::invalid_argument("Hibas template parameter");
    /// @brief kivételek a get<T> templatenak
    std::invalid_argument nincs_mezo = std::invalid_argument("A Jegy osztalynak nincs ilyen mezoje");

    /// @brief mezőt nevesítő stringből megfelelő típust hoz létre
    /// @param a - mezőt nevesítő String
    /// @return JegyAttr a megfelelő mezőhőz vagy JegyAttr::ismeretlen ha nincs ilyen mező
    JegyAttr toJegyAttr(const String& a) const;

    /// @brief mezőt nevesítő String alapján referenciát ad arra a mezőre
    /// @tparam T - a mező típusa
    /// @param attr - mezőt nevesítő String
    /// @return referencia a nevesített mezőre
    /// helytelen típus vagy nem létező mezőnév megadása esetén kivételt dob
    template<typename T>
    T& get(const String& attr) {
        JegyAttr jegyA = this->toJegyAttr(attr);

        if (jegyA == JegyAttr::ismeretlen) throw nincs_mezo;
        throw hibas_tipus;
    }
};

/// @brief get<T> template specializáció Vonat* típusra
template<>
Vonat*& Jegy::get<Vonat*>(const String& attr);

/// @brief get<T> template specializáció String típusra
template<>
String& Jegy::get<String>(const String& attr);

/// @brief get<T> template specializáció int típusra
template<>
int& Jegy::get<int>(const String& attr);

/// @brief get<T> template specializáció double típusra
template<>
double& Jegy::get<double>(const String& attr);

/// @brief get<T> template specializáció bool típusra
template<>
bool& Jegy::get<bool>(const String& attr);

#endif