#ifndef STRING_H
#define STRING_H
/**
 * \file String.h
 * 
 * Ez a fájl tartalmazza az ötödik laborfeladatnak megfelelő string osztály implementációt.
 */

#include <iostream>


/**
 * String osztály
 * A pData tartalmazza a karaktereket a lezáró nullával együtt
 * hossz: a String hossz a lezáró nulla nélkül
 */
class String {
    char *pData;        ///< pointer az adatra
    size_t hossz;       ///< hossz lezáró nulla nélkül
public:
    /// konstrktor karakterből
    /// @param c - karakter
    String(char c);

    /// Konstruktor egy nullával lezárt karaktersorozatból
    /// @param p - pointer egy C stringre
    String(const char *p = "");

    /// Másoló konstruktor
    /// @param s1 - String amiből másolunk
    String(const String& s1);

    /// Hossz lekérdezése
    /// @return String hossza
    inline size_t size() const { return hossz; }

    /// C-stringet ad vissza
    /// @return pointer egy C-stringre
    inline const char* c_str() const { return pData; }
    
    /// Értékadó operátor
    /// @param rhs_s - jobboldali String
    /// @return modosított string referenciája
    String& operator=(const String& rhs_s);

    /// Két stringet összefűz
    /// @param rhs_s - jobboldali String
    /// @return új String ami a két stringet tartalmazza egymás után
    String operator+(const String& rhs_s) const;

    /// Stringhez karaktert fűz
    /// @param c - jobboldali karakter
    /// @return új String ami a régi String + karakter
    String operator+(char c) const;

    /// A String adott indexű karakterét adja vissza
    /// @param idx - karakter indexe
    /// @return karakter referencia
    /// Indexelési hiba esetén const char* kivételt dob
    char& operator[](size_t idx);   

    /// A String adott indexű karakterét adja vissza
    /// @param idx - karakter indexe
    /// @return karakter referencia
    /// Indexelési hiba esetén const char* kivételt dob
    const char& operator[](size_t idx) const;
    
    /// Destruktor
    ~String() { delete[] pData; }
};

/// Stringet ír az ostream-re
/// @param os - ostream
/// @param str - String
/// @return os
std::ostream& operator<<(std::ostream& os, const String& str);

/// istream-ről egy szót olvas be Stringbe
/// @param is - istream
/// @param s0 - String
/// @return is
std::istream& operator>>(std::istream& is, String& s0);

/// Karakterhez Stringet fűz
/// @param ch - karakter
/// @param str - String
/// @return új String, karakter + String
String operator+(char ch, const String& str);

#endif