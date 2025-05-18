#ifndef DYN_ARRAY_HPP
#define DYN_ARRAY_HPP
/**
 * \file dyn_arrary.hpp
 * 
 * Ez a fájl tartalmazza a specifikáció szerinti dyn_array<T> template megvalósítását.
 */

#include <stdexcept>


/// @brief automatikusan méretet változtató tömb tetszőleges típus tárolására
/// @tparam T - tárolt adat típusa
template <typename T>
class dyn_array {
    T* pData;               ///< foglalt memória területre mutató pointer
    int occupied;           ///< tárolt elemek száma
    int capacity;           ///< tömb kapacitása (foglalt terület mérete)
public:
    /// @brief Konstruktor
    /// @param c - tömb kapacitása (1)
    dyn_array(int c = 1): pData(new T[c]), occupied(0), capacity(c) {};
    
    /// @brief Egy elem hozzáadása a tömb végére
    /// @param element - elem amit hozzáadunk
    void append(T element) {
        // ha van hely hozzáadjuk
        if (occupied < capacity) {
            pData[occupied++] = element;
        } else {
            // ha nincs növeljük a foglalt terület méretét
            capacity = capacity * 2;
            T* pData_new = new T[capacity];
            for (int i = 0; i < occupied; i++) {
                pData_new[i] = pData[i];
            }
            delete[] pData;
            pData = pData_new;
            pData[occupied++] = element;
        }
    }

    /// @brief adott indexű elem törlése (hibás index esetén kivételt dob)
    /// @param idx - index amit törlünk
    void arr_delete(int idx)  {
        if (idx >= 0 && idx <= occupied) {
            for (int i = idx; i < occupied-1; i++) {
                pData[i] = pData[i + 1];
            }
            occupied--;
            // ha nagyon kevés elem van már csak a tömbben akkor csökkentjük a foglalt terület méretét
            if ((occupied / capacity) <= 0.5) {
                capacity = (int)(0.75 * capacity) + 1;
                T* pData_new = new T[capacity];
                for (int i = 0; i < occupied; i++) {
                    pData_new[i] = pData[i];
                }
                delete[] pData;
                pData = pData_new;
            }
        } else {
            throw std::out_of_range("dyn_array: hibas index");
        }
    }

    /// @brief tárolt adatok elérése, túlindexelés esetén kivételt dob
    /// @param idx - index
    /// @return referencia adott indexű tömbelemre  
    T& operator[](int idx) {
        if (idx >= 0 && idx < occupied) {
            return pData[idx];
        } else {
            throw std::out_of_range("dyn_array: hibas index");
        }
    }

    /// @brief tömbben foglalt helyek száma
    /// @return hány elem van a tömbben 
    int occ() const {
        return occupied;
    }

    /// @brief Destruktor (felszabadítja a memóriát)
    ~dyn_array() {
        delete[] pData;
    };
};


#endif