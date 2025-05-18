#include <stdexcept>
#include <cstring>

#include "Vonat.hpp"

/// @brief Vonat osztály egy mezőjének elérése
String Vonat::operator[](const String& attr) const {
    switch (this->toVonatAttr(attr))
    {
    case VonatAttr::vonatszam:
        return String(std::to_string(vonatszam).c_str());
        break;
    case VonatAttr::indulasi_allomas:
        return indulasi_allomas;
        break;
    case VonatAttr::indulasi_ido:
        return indulasi_ido;
        break;
    case VonatAttr::erkezesi_allomas:
        return erkezesi_allomas;
        break;
    case VonatAttr::erkezesi_ido:
        return erkezesi_ido;
        break;
    default:
        throw std::invalid_argument("A Vonat osztalynak nincs ilyen mezoje.");
        break;
    }
}

/// @brief mezőt nevesítő Stringből megfelelő típust hoz létre
Vonat::VonatAttr Vonat::toVonatAttr(const String& a) const {
    if (std::strcmp(a.c_str(), "vonatszam") == 0) return VonatAttr::vonatszam;
    if (std::strcmp(a.c_str(), "indulasi_allomas") == 0) return VonatAttr::indulasi_allomas;
    if (std::strcmp(a.c_str(), "indulasi_ido") == 0) return VonatAttr::indulasi_ido;
    if (std::strcmp(a.c_str(), "erkezesi_allomas") == 0) return VonatAttr::erkezesi_allomas;
    if (std::strcmp(a.c_str(), "erkezesi_ido") == 0) return VonatAttr::erkezesi_ido;
    return VonatAttr::ismeretlen;
}

/// @brief get<T> template specializáció String típusra
template<>
String& Vonat::get<String>(const String& attr) {
    VonatAttr vonatA = this->toVonatAttr(attr);

    switch (vonatA)
    {
        case VonatAttr::indulasi_allomas:
            return indulasi_allomas;
            break;
        case VonatAttr::indulasi_ido:
            return indulasi_ido;
            break;
        case VonatAttr::erkezesi_allomas:
            return erkezesi_allomas;
            break;
        case VonatAttr::erkezesi_ido:
            return erkezesi_ido;
            break;
        case VonatAttr::ismeretlen:
            throw nincs_mezo;
            break;
        default:
            throw hibas_tipus;
            break;
    }
}

/// @brief get<T> template specializáció int típusra
template<>
int& Vonat::get<int>(const String& attr) {
    VonatAttr vonatA = this->toVonatAttr(attr);

    if (vonatA == VonatAttr::vonatszam) return vonatszam;
    if (vonatA == VonatAttr::ismeretlen) throw nincs_mezo;
    throw hibas_tipus;
}
