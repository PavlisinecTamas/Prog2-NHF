#ifndef MENU_H
#define MENU_H

#include "Vonat.hpp"
#include "Jegy.hpp"
#include "dyn_array.hpp"

class Menu {
    bool running = true;
    dyn_array<Vonat> vonatok;
    dyn_array<Jegy> jegyek;
    enum class MenuState {
        Alap,
        VonatAdat,
        JegyAdat,
        VonatFel,
        VonatTor,
        JegyKi,
        Menetrend,
        Eladasok,
        Kilep
    };
    MenuState current = MenuState::Alap;
    
    void alap();
    void vonatadat();
    void jegyadat();
    void vonatfel();
    void vonattor();
    void jegyki();
    void menetrend();
    void eladasok();
    Vonat* find_vonat(const int vsz);
    bool str_to_bool(const String& s) const;

public:
    Menu(): vonatok(dyn_array<Vonat>()), jegyek(dyn_array<Jegy>()) {};

    inline bool active() const {return running;}

    void nextState();
};

#endif