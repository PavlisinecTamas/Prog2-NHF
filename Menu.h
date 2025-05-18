#ifndef MENU_H
#define MENU_H

/**
 * \file Menu.h
 * 
 * A Specifikáció szerinti felhasználói felületet megvalósító objektum.
 */

#include "Vonat.hpp"
#include "Jegy.hpp"
#include "dyn_array.hpp"

/// @brief A Felhasználói felületet megvalósító objektum
class Menu {
    bool running = true;                ///< Igaz amíg a felhasználó nem ad kilépésre utasítást
    dyn_array<Vonat> vonatok;           ///< A tárolt vonatok
    dyn_array<Jegy> jegyek;             ///< A tárolt jegyek
    std::istream& cinput;               ///< A kimenet erre a streamre megy
    std::ostream& coutput;              ///< A bemenet erről a streamről jön
    
    /// @brief A menü állapotát megadó enum
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

    /// @brief jelenlegi állapot
    MenuState current = MenuState::Alap;
    
    /// @brief állapotokhoz tartozó függvények
    void alap();
    /// @brief állapotokhoz tartozó függvények
    void vonatadat();
    /// @brief állapotokhoz tartozó függvények
    void jegyadat();
    /// @brief állapotokhoz tartozó függvények
    void vonatfel();
    /// @brief állapotokhoz tartozó függvények
    void vonattor();
    /// @brief állapotokhoz tartozó függvények
    void jegyki();
    /// @brief állapotokhoz tartozó függvények
    void menetrend();
    /// @brief állapotokhoz tartozó függvények
    void eladasok();
    /// @brief adott vonatszámú vonatot talál
    Vonat* find_vonat(const int vsz);

    void talalat(int idx, bool& d_a, bool& c);

    /// @brief Stringet boolá alakít
    /// @param s - String amit át kell alakítani
    /// @return true ha s = "True" false ha s = "False"
    bool str_to_bool(const String& s) const;

public:
    /// @brief konstruktor
    /// @param ci - input stream
    /// @param co - output stream
    Menu(std::istream& ci = std::cin, std::ostream& co = std::cout): vonatok(dyn_array<Vonat>()), jegyek(dyn_array<Jegy>()), cinput(ci), coutput(co) {};

    /// @brief Menü állapot lekérdezéséhez
    /// @return igaz ha a user nem kért kilépést
    inline bool active() const {return running;}

    /// @brief EOF-et és input stream hibákat kezel
    /// @param dob - dobjon-e kivételt ha valami gond van
    void check_cin(bool dob);

    /// @brief A menü megfelelő állapotába lép a bemenet alapján
    void nextState();
};

#endif