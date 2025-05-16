#ifndef DYN_ARRAY_HPP
#define DYN_ARRAY_HPP

#include <stdexcept>


template <typename T>
class dyn_array {
    T* pData;
    int occupied;
    int capacity;
public:
    dyn_array(int c = 1): pData(new T[c]), occupied(0), capacity(c) {};
    
    void append(T element) {
        if (occupied < capacity) {
            pData[occupied++] = element;
        } else {
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

    void arr_delete(int idx)  {
        if (idx >= 0 && idx <= occupied) {
            for (int i = idx; i < occupied; i++) {
                pData[i] = pData[i + 1];
            }
            occupied--;
            if ((capacity / occupied) <= 0.5) {
                capacity = (int)(0.75 * capacity);
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

    T& operator[](int idx) {
        if (idx >= 0 && idx <= occupied) {
            return pData[0];
        } else {
            throw std::out_of_range("dyn_array: hibas index");
        }
    }

    int occ() const {
        return occupied;
    }

    ~dyn_array() {
        delete[] pData;
    };
};


#endif