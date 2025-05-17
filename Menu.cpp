#include <iostream>
#include <fstream>
#include <cstring>
#include <limits>

#include "Menu.h"
#include "Vonat.hpp"
#include "Jegy.hpp"


void Menu::alap()  {
    std::cout << std::endl;
    std::cout << "============ E V E R ============" << std::endl;
    std::cout << "Egyszerű Vonatjegy Eladó Rendszer" << std::endl;

    std::cout << "\t1. Vonat adatbázis betöltése/mentése " << std::endl;
    std::cout << "\t2. Jegy adatbázis betöltése/mentése " << std::endl;
    std::cout << "\t3. Vonat felvétele " << std::endl;
    std::cout << "\t4. Vonat törlése " << std::endl;
    std::cout << "\t5. Jegy kiadása " << std::endl;
    std::cout << "\t6. Menetrend generálása " << std::endl;
    std::cout << "\t7. Eladások összesítése " << std::endl;
    std::cout << "\t8. Kilépés " << std::endl;    

    int valasztas = 0;
    while (!(valasztas >= 1 && valasztas <= 8)) {
        std::cout << "Művelet választás(1-8): ";
        std::cin >> valasztas;
        if (std::cin.eof()) {
            std::exit(-1);
        }
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    switch (valasztas) 
    {
        case 1: current = MenuState::VonatAdat; break;
        case 2: current = MenuState::JegyAdat; break;
        case 3: current = MenuState::VonatFel; break;
        case 4: current = MenuState::VonatTor; break;
        case 5: current = MenuState::JegyKi; break;
        case 6: current = MenuState::Menetrend; break;
        case 7: current = MenuState::Eladasok; break;
        case 8: current = MenuState::Kilep; break;
        default:
            throw std::invalid_argument("Menu: helytelen valasztas");
            break;
    }
}

void Menu::vonatadat() {
    char valasz = 'c';
    while (!(valasz == 'b' || valasz == 'm')) {
        std::cout << "Vonat adatbázis betölt/ment? (b vagy m): ";
        std::cin >> valasz;
    }
    String fajlnev;
    std::cout << "Fájlnév: ";
    std::cin >> fajlnev;
    if (valasz == 'b') {
        std::ifstream VonatBe(fajlnev.c_str());

        String sor;
        while (VonatBe.good()) {
            VonatBe >> sor;
            const char* c_s = sor.c_str();
            // vonatszam, indulasi_a, indulasi_i, erkezesi_a, erkezesi_i
            String attribs[5];
            int attr_idx = 0;
            for (size_t i = 0; i < sor.size(); i++) {
                if (c_s[i] == ';') {
                    attr_idx++;
                } else {
                    attribs[attr_idx] = attribs[attr_idx] + c_s[i];
                }
            }
            vonatok.append(Vonat(std::atoi(attribs[0].c_str()), attribs[1].c_str(), attribs[2].c_str(), attribs[3].c_str(), attribs[4].c_str()));
        }
        if (VonatBe.is_open())
            std::cout << "[Válasz]: " << fajlnev << " beolvasása sikeres volt." << std::endl;
        else
            std::cout << "[Válasz]: " << fajlnev << " beolvasása sikertelen volt." << std::endl;
        VonatBe.close();
    }
    if (valasz == 'm') {
        std::ofstream VonatKi(fajlnev.c_str());

        for (int i = 0; i < vonatok.occ(); i++) {
            VonatKi << vonatok[i]["vonatszam"] << ';'
                << vonatok[i]["indulasi_allomas"] << ';'
                << vonatok[i]["indulasi_ido"] << ';'
                << vonatok[i]["erkezesi_allomas"] << ';'
                << vonatok[i]["erkezesi_ido"] << std::endl;
        }
        if (VonatKi.is_open())
            std::cout << "[Válasz]: " << fajlnev << " mentése sikeres volt." << std::endl;
        else
            std::cout << "[Válasz]: " << fajlnev << " mentése sikertelen volt." << std::endl;
        VonatKi.close();
    }
    current = MenuState::Alap;
}

Vonat* Menu::find_vonat(const int vsz) {
    // ha van ilyen vonat megkeressük
    for (int i = 0; i < vonatok.occ(); i++) {
        if (vonatok[i].get<int>("vonatszam") == vsz)
            return &(vonatok[i]);
    }
    // ha nincs akkor felveszünk egy újat
    vonatok.append(Vonat(vsz));
    return &(vonatok[vonatok.occ() - 1]);
}

bool Menu::str_to_bool(const String& s) const {
    int t = std::strcmp(s.c_str(), "True");
    int f = std::strcmp(s.c_str(), "False");

    if (t == 0)
        return true;
    if (f == 0)
        return false;
    throw std::invalid_argument("Jegy: Az adatbazisban helytelen formatumu a retur mezo");
}

void Menu::jegyadat() {
    char valasz = 'c';
    while (!(valasz == 'b' || valasz == 'm')) {
        std::cout << "Jegy adatbázis betölt/ment? (b vagy m): ";
        std::cin >> valasz;
    }
    String fajlnev;
    std::cout << "Fájlnév: ";
    std::cin >> fajlnev;
    if (valasz == 'b') {
        std::ifstream JegyBe(fajlnev.c_str());

        String sor;
        while (JegyBe.good()) {
            JegyBe >> sor;
            const char* c_s = sor.c_str();
            // vonat, kocsiszam, hely, ar, kedvezmenyek, kocsiosztaly, retur, elado_allomas
            String attribs[8];
            int attr_idx = 0;
            for (size_t i = 0; i < sor.size(); i++) {
                if (c_s[i] == ';') {
                    attr_idx++;
                } else {
                    attribs[attr_idx] = attribs[attr_idx] + c_s[i];
                }
            }
            jegyek.append(Jegy( find_vonat(std::atoi(attribs[0].c_str())), 
                std::atoi(attribs[1].c_str()), 
                attribs[2].c_str(), 
                std::atof(attribs[3].c_str()), 
                attribs[4].c_str(), 
                std::atoi(attribs[5].c_str()), 
                str_to_bool(attribs[6]), 
                attribs[7].c_str())
            );
        }
        if (JegyBe.is_open())
            std::cout << "[Válasz]: " << fajlnev << " beolvasása sikeres volt." << std::endl;
        else
            std::cout << "[Válasz]: " << fajlnev << " beolvasása sikertelen volt." << std::endl;
        JegyBe.close();
    }
    if (valasz == 'm') {
        std::ofstream JegyKi(fajlnev.c_str());

        for (int i = 0; i < jegyek.occ(); i++) {
            JegyKi << jegyek[i]["vonat"] << ';'
                << jegyek[i]["kocsiszam"] << ';'
                << jegyek[i]["hely"] << ';'
                << jegyek[i]["ar"] << ';'
                << jegyek[i]["kedvezmenyek"] << ';'
                << jegyek[i]["kocsiosztaly"] << ';'
                << jegyek[i]["retur"] << ';'
                << jegyek[i]["eladi_allomas"] << std::endl;
        }
        if (JegyKi.is_open())
            std::cout << "[Válasz]: " << fajlnev << " mentése sikeres volt." << std::endl;
        else
            std::cout << "[Válasz]: " << fajlnev << " mentése sikertelen volt." << std::endl;
        JegyKi.close();
    }
    current = MenuState::Alap;
}

static void check_cin() {
    if (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (std::cin.eof())
            std::exit(-1);
        throw std::invalid_argument("Menu::vonatfel: Hibas bemenet");
    }
}

void Menu::vonatfel() {
    std::cout << "Vonat felvétele: " << std::endl;
    current = MenuState::Alap;
    Vonat v;
    try {
        std::cout << "[Új vonat][vonatszam]: ";
        std::cin >> v.get<int>("vonatszam"); 
        check_cin();
        const int& vsz = v.get<int>("vonatszam");
        std::cout << '[' << vsz << ']' << "[indulasi_allomas]: ";
        std::cin >> v.get<String>("indulasi_allomas");
        check_cin();
        std::cout << '[' << vsz << ']' << "[indulasi_ido]: ";
        std::cin >> v.get<String>("indulasi_ido");
        check_cin();
        std::cout << '[' << vsz << ']' << "[erkezesi_allomas]: ";
        std::cin >> v.get<String>("erkezesi_allomas");
        check_cin();
        std::cout << '[' << vsz << ']' << "[erkezesi_ido]: ";
        std::cin >> v.get<String>("erkezesi_ido");
        check_cin();
        vonatok.append(v);
    } catch (...) {
        std::cout << "[Új vonat] Vonat felvétele sikertelen" << std::endl;
        return;
    }
    std::cout << '[' << v["vonatszam"] << ']' <<" Vonat felvétele sikeres" << std::endl;
}

void Menu::vonattor() {
    std::cout << ">>vonattor" << std::endl;
    current = MenuState::Alap;
}

void Menu::jegyki() {
    std::cout << ">>jegyki" << std::endl;
    current = MenuState::Alap;
}

void Menu::menetrend() {
    std::cout << ">>menetrend" << std::endl;
    current = MenuState::Alap;
}

void Menu::eladasok() {
    std::cout << ">>eladasok" << std::endl;
    current = MenuState::Alap;
}

void Menu::nextState() {
    switch (current)
    {
    case MenuState::Alap:       alap(); break;
    case MenuState::VonatAdat:  vonatadat(); break;
    case MenuState::JegyAdat:   jegyadat(); break;
    case MenuState::VonatFel:   vonatfel(); break;
    case MenuState::VonatTor:   vonattor(); break;
    case MenuState::JegyKi:     jegyki(); break;
    case MenuState::Menetrend:  menetrend(); break;
    case MenuState::Eladasok:   eladasok(); break;
    case MenuState::Kilep:
        running = false;
        break;
    default:
        throw std::invalid_argument("Menu: helytelen allapot");
        break;
    }
}