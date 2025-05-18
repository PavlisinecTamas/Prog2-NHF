#include <stdexcept>
#include <cstring>

#include "Jegy.hpp"
#include "String.h"

/// @brief Két jegy minden mezőjének egynelőségét vizsgálja
bool Jegy::operator==(const Jegy& j) const {
    return (
        vonat == j.vonat &&
        kocsiszam == j.kocsiszam &&
        strcmp(hely.c_str(), j.hely.c_str()) == 0 &&
        ar == j.ar &&
        strcmp(kedvezmenyek.c_str(), j.kedvezmenyek.c_str()) == 0 &&
        kocsiosztaly == j.kocsiosztaly &&
        retur == j.retur &&
        strcmp(elado_allomas.c_str(), j.elado_allomas.c_str()) == 0
    );
}

/// @brief két jegy minden mezőjének egyenlőségét vizsgálja
bool Jegy::operator!=(const Jegy& j) const {
    return !(this->operator==(j));
}

/// @brief két jegy árának összehasonlítása
bool Jegy::operator>(const Jegy& j) const {
    return ar > j.ar;
}

/// @brief két jegy árának összehasonlítása
bool Jegy::operator<(const Jegy& j) const {
    return ar < j.ar;
}

/// @brief Jegy egy mezőjének elérése 
String Jegy::operator[](const String& attr) const {
    switch (this->toJegyAttr(attr))
    {
    case JegyAttr::vonat:
        return (*vonat)["vonatszam"];
        break;
    case JegyAttr::kocsiszam:
        return String(std::to_string(kocsiszam).c_str());
        break;
    case JegyAttr::hely:
        return hely;
        break;
    case JegyAttr::ar:
        return String(std::to_string(ar).c_str());
        break;
    case JegyAttr::kedvezmenyek:
        return kedvezmenyek;
        break;
    case JegyAttr::kocsiosztaly:
        return String(std::to_string(kocsiosztaly).c_str());
        break;
    case JegyAttr::retur:
        return ((retur) ? String("True") : String("False"));
        break;
    case JegyAttr::elado_allomas:
        return elado_allomas;
        break;
    default:
        throw nincs_mezo;
        break;
    }
}

/// @brief mezőt nevesítő stringből megfelelő típust hoz létre
Jegy::JegyAttr Jegy::toJegyAttr(const String& a) const {
    if (std::strcmp(a.c_str(), "vonat") == 0) return JegyAttr::vonat;
    if (std::strcmp(a.c_str(), "kocsiszam") == 0) return JegyAttr::kocsiszam;
    if (std::strcmp(a.c_str(), "hely") == 0) return JegyAttr::hely;
    if (std::strcmp(a.c_str(), "ar") == 0) return JegyAttr::ar;
    if (std::strcmp(a.c_str(), "kedvezmenyek") == 0) return JegyAttr::kedvezmenyek;
    if (std::strcmp(a.c_str(), "kocsiosztaly") == 0) return JegyAttr::kocsiosztaly;
    if (std::strcmp(a.c_str(), "retur") == 0) return JegyAttr::retur;
    if (std::strcmp(a.c_str(), "elado_allomas") == 0) return JegyAttr::elado_allomas;

    return JegyAttr::ismeretlen;
}

/// @brief get<T> template specializáció Vonat* típusra
template<>
Vonat*& Jegy::get<Vonat*>(const String& attr) {
    JegyAttr jegyA = this->toJegyAttr(attr);

    if (jegyA == JegyAttr::vonat) return vonat;
    if (jegyA == JegyAttr::ismeretlen) throw nincs_mezo;
    throw hibas_tipus;
}

/// @brief get<T> template specializáció String típusra
template<>
String& Jegy::get<String>(const String& attr) {
    JegyAttr jegyA = this->toJegyAttr(attr);

    switch (jegyA) 
    {
        case JegyAttr::hely:
            return hely;
            break;
        case JegyAttr::kedvezmenyek:
            return kedvezmenyek;
            break;
        case JegyAttr::elado_allomas:
            return elado_allomas;
            break;
        case JegyAttr::ismeretlen:
            throw nincs_mezo;
            break;
        default:
            throw hibas_tipus;
            break;
    }
}

/// @brief get<T> template specializáció int típusra
template<>
int& Jegy::get<int>(const String& attr) {
    JegyAttr jegyA = this->toJegyAttr(attr);

    switch (jegyA)
    {
        case JegyAttr::kocsiszam:
            return kocsiszam;
            break;
        case JegyAttr::kocsiosztaly:
            return kocsiosztaly;
            break;
        case JegyAttr::ismeretlen:
            throw nincs_mezo;
            break;
        default:
            throw hibas_tipus;
            break;
    }
}

/// @brief get<T> template specializáció double típusra
template<>
double& Jegy::get<double>(const String& attr) {
    JegyAttr jegyA = this->toJegyAttr(attr);

    if (jegyA == JegyAttr::ar) return ar;
    if (jegyA == JegyAttr::ismeretlen) throw nincs_mezo;
    throw hibas_tipus;
}

/// @brief get<T> template specializáció bool típusra
template<>
bool& Jegy::get<bool>(const String& attr) {
    JegyAttr jegyA = this->toJegyAttr(attr);

    if (jegyA == JegyAttr::retur) return retur;
    if (jegyA == JegyAttr::ismeretlen) throw nincs_mezo;
    throw hibas_tipus;
}