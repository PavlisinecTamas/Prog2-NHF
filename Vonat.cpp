#include <stdexcept>
#include <cstring>

#include "Vonat.hpp"

Vonat::Vonat(const Vonat& v) {
    vonatszam = v.vonatszam;
    indulasi_allomas = v.indulasi_allomas;
    indulasi_ido = v.indulasi_ido;
    erkezesi_allomas = v.erkezesi_allomas;
    erkezesi_ido = v.erkezesi_ido;
}

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

Vonat::VonatAttr Vonat::toVonatAttr(const String& a) const {
    if (std::strcmp(a.c_str(), "vonatszam")) return VonatAttr::vonatszam;
    if (std::strcmp(a.c_str(), "indulasi_allomas")) return VonatAttr::indulasi_allomas;
    if (std::strcmp(a.c_str(), "indulasi_ido")) return VonatAttr::indulasi_ido;
    if (std::strcmp(a.c_str(), "erkezesi_allomas")) return VonatAttr::erkezesi_allomas;
    if (std::strcmp(a.c_str(), "erkezesi_ido")) return VonatAttr::erkezesi_ido;
    return VonatAttr::ismeretlen;
}

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

template<>
int& Vonat::get<int>(const String& attr) {
    VonatAttr vonatA = this->toVonatAttr(attr);

    if (vonatA == VonatAttr::vonatszam) return vonatszam;
    if (vonatA == VonatAttr::ismeretlen) throw nincs_mezo;
    throw hibas_tipus;
}
