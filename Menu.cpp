#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <limits>

#include "Menu.h"
#include "Vonat.hpp"
#include "Jegy.hpp"

void Menu::check_cin(bool dob = false) {
    if (!cinput.good()) {
        cinput.clear();
        cinput.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (cinput.eof())
            std::exit(-1);
        if (dob)
            throw std::invalid_argument("Menu: Hibas bemenet");
    }
}

void Menu::alap()  {
    coutput << std::endl;
    coutput << "============ E V E R ============" << std::endl;
    coutput << "Egyszerű Vonatjegy Eladó Rendszer" << std::endl;

    coutput << "\t1. Vonat adatbázis betöltése/mentése " << std::endl;
    coutput << "\t2. Jegy adatbázis betöltése/mentése " << std::endl;
    coutput << "\t3. Vonat felvétele " << std::endl;
    coutput << "\t4. Vonat törlése " << std::endl;
    coutput << "\t5. Jegy kiadása " << std::endl;
    coutput << "\t6. Menetrend generálása " << std::endl;
    coutput << "\t7. Eladások összesítése " << std::endl;
    coutput << "\t8. Kilépés " << std::endl;    

    int valasztas = 0;
    while (!(valasztas >= 1 && valasztas <= 8)) {
        coutput << "Művelet választás(1-8): ";
        cinput >> valasztas;
        check_cin();
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
    char valasz2 = 'c';
    while (!(valasz == 'b' || valasz == 'm')) {
        cinput.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        coutput << "Vonat adatbázis betölt/ment? (b vagy m): ";
        cinput >> valasz;
        check_cin();
    }
    if (valasz == 'b') {
        while (!(valasz2 == 'i' || valasz2 == 'n')) {
            cinput.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            coutput << "Vonat adatbázis felülír? (i vagy n): ";
            cinput >> valasz2;
            check_cin();
        }
    }
    if (valasz2 == 'i') {
        while (vonatok.occ() > 0)
        vonatok.arr_delete(0);
    }
    String fajlnev;
    coutput << "Fájlnév: ";
    cinput >> fajlnev;
    check_cin();
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
            coutput << "[Válasz]: " << fajlnev << " beolvasása sikeres volt." << std::endl;
        else
            coutput << "[Válasz]: " << fajlnev << " beolvasása sikertelen volt." << std::endl;
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
            coutput << "[Válasz]: " << fajlnev << " mentése sikeres volt." << std::endl;
        else
            coutput << "[Válasz]: " << fajlnev << " mentése sikertelen volt." << std::endl;
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
    throw std::invalid_argument("Jegy: helytelen formatumu a retur mezo");
}

void Menu::jegyadat() {
    char valasz = 'c';
    char valasz2 = 'c';
    while (!(valasz == 'b' || valasz == 'm')) {
        cinput.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        coutput << "Jegy adatbázis betölt/ment? (b vagy m): ";
        cinput >> valasz;
        check_cin();
    }
    if (valasz == 'b') {
        while (!(valasz2 == 'i' || valasz2 == 'n')) {
            cinput.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            coutput << "Jegy adatbázis felülír? (i vagy n): ";
            cinput >> valasz2;
            check_cin();
        }
    }
    if (valasz2 == 'i') {
        while (jegyek.occ() > 0)
            jegyek.arr_delete(0);
    }
    String fajlnev;
    coutput << "Fájlnév: ";
    cinput >> fajlnev;
    check_cin();
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
            coutput << "[Válasz]: " << fajlnev << " beolvasása sikeres volt." << std::endl;
        else
            coutput << "[Válasz]: " << fajlnev << " beolvasása sikertelen volt." << std::endl;
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
                << jegyek[i]["elado_allomas"] << std::endl;
        }
        if (JegyKi.is_open())
            coutput << "[Válasz]: " << fajlnev << " mentése sikeres volt." << std::endl;
        else
            coutput << "[Válasz]: " << fajlnev << " mentése sikertelen volt." << std::endl;
        JegyKi.close();
    }
    current = MenuState::Alap;
}

void Menu::vonatfel() {
    coutput << "Vonat felvétele (whitespace eldobásra kerül): " << std::endl;
    current = MenuState::Alap;
    Vonat v;
    try {
        coutput << "[Új vonat][vonatszam]: ";
        cinput >> v.get<int>("vonatszam"); 
        check_cin(true);
        const int& vsz = v.get<int>("vonatszam");
        coutput << '[' << vsz << ']' << "[indulasi_allomas]: ";
        cinput >> v.get<String>("indulasi_allomas");
        check_cin(true);
        coutput << '[' << vsz << ']' << "[indulasi_ido]: ";
        cinput >> v.get<String>("indulasi_ido");
        check_cin(true);
        coutput << '[' << vsz << ']' << "[erkezesi_allomas]: ";
        cinput >> v.get<String>("erkezesi_allomas");
        check_cin(true);
        coutput << '[' << vsz << ']' << "[erkezesi_ido]: ";
        cinput >> v.get<String>("erkezesi_ido");
        check_cin(true);
        vonatok.append(v);
    } catch (...) {
        coutput << "[Új vonat] Vonat felvétele sikertelen" << std::endl;
        return;
    }
    coutput << '[' << v["vonatszam"] << ']' <<" Vonat felvétele sikeres" << std::endl;
}

void Menu::vonattor() {
    coutput << "Melyik mező alapján történjen a törlés?" << std::endl;

    coutput << "\t1. vonatszam" << std::endl;
    coutput << "\t2. indulasi_allomas" << std::endl;    
    coutput << "\t3. indulasi_ido" << std::endl;
    coutput << "\t4. erkezesi_allomas" << std::endl;
    coutput << "\t5. erkezesi_ido" << std::endl;

    int valasztas = 0;
    while (!(valasztas >= 1 && valasztas <= 5)) {
        coutput << "Mező választás(1-5):";
        cinput >> valasztas;
        check_cin();
    }
    coutput << (Vonat::VonatAttr::vonatszam == Vonat::VonatAttr(1)) << std::endl;
    current = MenuState::Alap;
}

void Menu::jegyki() {
    coutput << "Jegy kiadása (whitespace eldobásra kerül): " << std::endl;
    current = MenuState::Alap;
    Jegy j;
    try {
        coutput << "[Új Jegy][vonatszam]: ";
        int vsz = 0;
        cinput >> vsz;
        check_cin(true);
        j.get<Vonat*>("vonat") = find_vonat(vsz);
        coutput << "[Új Jegy][kocsiszam]: ";
        cinput >> j.get<int>("kocsiszam");
        check_cin(true);
        coutput << "[Új Jegy][hely]: ";
        cinput >> j.get<String>("hely");
        check_cin(true);
        coutput << "[Új Jegy][ar]: ";
        cinput >> j.get<double>("ar");
        check_cin(true);
        coutput << "[Új Jegy][kedvezmenyek]: ";
        cinput >> j.get<String>("kedvezmenyek");
        check_cin(true);
        coutput << "[Új Jegy][kocsiosztaly]: ";
        cinput >> j.get<int>("kocsiosztaly");
        check_cin(true);
        coutput << "[Új Jegy][retur](True/False): ";
        String temp;
        cinput >> temp;
        check_cin(true);
        j.get<bool>("retur") = str_to_bool(temp);
        coutput << "[Új Jegy][elado_allomas]: ";
        cinput >> j.get<String>("elado_allomas"); 
        check_cin(true);
        jegyek.append(j);
    } catch (...) {
        coutput << "[Új Jegy] Jegy kiadása sikertelen" << std::endl;
        return;
    }
    coutput << "[Új Jegy] Jegy kiadása sikeres" << std::endl;    
}

void Menu::menetrend() {
    std::ostringstream os;
    for (int i = 0; i < vonatok.occ(); i++) {
        os << "Vonatszám: " << vonatok[i]["vonatszam"] << '\t'
                << "Honnan: " << vonatok[i]["indulasi_allomas"] << '\t'
                << "Indul: " << vonatok[i]["indulasi_ido"] << '\t'
                << "Hova: " << vonatok[i]["erkezesi_allomas"] << '\t'
                << "Érkezik: " << vonatok[i]["erkezesi_ido"] << std::endl;
    }
    coutput << os.str() << std::endl;
    char valasz = 'c';
    while (!(valasz == 'i' || valasz == 'n')) {
        cinput.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        coutput << std::endl << "Menetrend mentése? (i vagy n): ";
        cinput >> valasz;
        check_cin();
    }
    if (valasz == 'i') {
        String fajlnev;
        coutput << "Fájlnév: ";
        cinput >> fajlnev;
        check_cin();

        std::ofstream MenetrendKi(fajlnev.c_str());

        MenetrendKi << os.str() << std::endl;

        if (MenetrendKi.is_open())
            coutput << "[Válasz]: " << fajlnev << " mentése sikeres volt." << std::endl;
        else
            coutput << "[Válasz]: " << fajlnev << " mentése sikertelen volt." << std::endl;
        MenetrendKi.close();
    }
    current = MenuState::Alap;
}

void Menu::eladasok() {
    std::ostringstream os;
    for (int i = 0; i < jegyek.occ(); i++) {
        os << "Vonatszám: " << jegyek[i]["vonat"] << '\t' 
                << "Honnan: " << jegyek[i].get<Vonat*>("vonat")->operator[]("indulasi_allomas") << '\t'
                << "Hova: " << jegyek[i].get<Vonat*>("vonat")->operator[]("erkezesi_allomas") << '\t'
                << "Kocsiszám: " << jegyek[i]["kocsiszam"] << '\t'
                << "Hely: " << jegyek[i]["hely"] << '\t'
                << "Ár: " << jegyek[i]["ar"] << '\t'
                << "Kervezmények: " << jegyek[i]["kedvezmenyek"] << '\t'
                << "Kocsiosztály: " << jegyek[i]["kocsiosztaly"] << '\t'
                << "Retúr jegy: " << jegyek[i]["retur"] << '\t'
                << "Eladás helye: " << jegyek[i]["elado_allomas"] << std::endl;
    }
    coutput << os.str() << std::endl;
    char valasz = 'c';
    while (!(valasz == 'i' || valasz == 'n')) {
        cinput.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        coutput << std::endl << "Eladás összesítés mentése? (i vagy n): ";
        cinput >> valasz;
        check_cin();
    }
    if (valasz == 'i') {
        String fajlnev;
        coutput << "Fájlnév: ";
        cinput >> fajlnev;
        check_cin();

        std::ofstream EladasokKi(fajlnev.c_str());

        EladasokKi << os.str() << std::endl;

        if (EladasokKi.is_open())
            coutput << "[Válasz]: " << fajlnev << " mentése sikeres volt." << std::endl;
        else    
            coutput << "[Válasz]: " << fajlnev << " mentése sikertelen volt." << std::endl;
        EladasokKi.close();
    }
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