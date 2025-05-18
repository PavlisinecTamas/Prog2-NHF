#ifndef MENU_H
#define MENU_H

#include "Vonat.hpp"
#include "Jegy.hpp"
#include "dyn_array.hpp"

class Menu {
    bool running = true;
    dyn_array<Vonat> vonatok;
    dyn_array<Jegy> jegyek;
    std::istream& cinput;
    std::ostream& coutput;
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
    Menu(std::istream& ci = std::cin, std::ostream& co = std::cout): vonatok(dyn_array<Vonat>()), jegyek(dyn_array<Jegy>()), cinput(ci), coutput(co) {};

    inline bool active() const {return running;}
    void check_cin(bool dob);
    void nextState();
};

#endif